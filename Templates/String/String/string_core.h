#ifndef STRING_core_H
#define STRING_core_H

#include <cstddef>
#include <cstdlib>
#include <cassert>
#include "allocator.h"
#include "error_codes.h"

const size_t SMALL_SIZE = 8;

// ------------------------------------------------------------------
// --------------------------- Shared ptr ---------------------------
// ------------------------------------------------------------------

template < typename DataT >
class Shared_data {
  public:
	DataT data_;
	size_t viewers;

	Shared_data(DataT&& other)
	: data_(std::move(other)), viewers(0) {}

	void view() {
		++viewers;
		printf("[Shared_data::view] viewers: %ld\n", viewers);
	}

	void unview() {
		--viewers;
		printf("[Shared_data::unview] viewers: %ld\n", viewers);
	}

	size_t get_viewers() const {
		return viewers;
	}
};

template < typename DataT >
class Shared_ptr {
	Shared_data<DataT>* ptr_;
	Allocator<Shared_data<DataT>> allocator_;

  public:

	Shared_ptr(Shared_data<DataT>* other)
	: ptr_(other) {
		ptr_->view();
	}

	Shared_ptr(const Shared_ptr& other)
	: ptr_(other.ptr_) {
		ptr_->view();
	}

	Shared_ptr(Shared_ptr&& other)
	: ptr_(other.ptr_) {
		other.ptr_ = nullptr;
	}

	Shared_ptr(DataT* data) {
		ptr_ = allocator_.allocate(1);
		new (ptr_) Shared_data<DataT>(std::move(*data));
		ptr_->view();
	}

	~Shared_ptr() {
		if (ptr_) {
			ptr_->unview();
		}
	}

	Shared_ptr& operator=(const Shared_ptr& other) {
		ptr_ = other.ptr_;
		ptr_->view();
		return *this;
	}

	Shared_ptr& operator=(Shared_ptr&& other) {
		ptr_ = other.ptr_;
		other.ptr_ = nullptr;
		return *this;
	}

	void view() {
		ptr_->view();
	}

	void unview() {
		ptr_->unview();
	}

	size_t get_viewers() const {
		return ptr_->get_viewers();
	}

	DataT operator*() {
		return ptr_->data_;
	}

	DataT& operator*() const {
		return ptr_->data_;
	}

	DataT* operator->() {
		return &(ptr_->data_);
	}

	DataT* operator->() const {
		return &(ptr_->data_);
	}

	Shared_data<DataT>* get_ptr() {
		return ptr_;
	}
};

// ------------------------------------------------------------------
// ------------------------- String core ----------------------------
// ------------------------------------------------------------------

enum class String_state {
	SSO,
	DYNAMIC,
	VIEW,
	NOT_OWNER
};

template < typename CharT >
class String_core {
  private:
	friend class Shared_data<String_core>;
	friend class Shared_ptr<String_core>;

	using Shared_ptr_ = Shared_ptr<String_core>;

	size_t size_{0};

	struct Dynamic_data {
		CharT* data_;
		size_t capacity_;
	};

	union {
		Dynamic_data data_;
		Shared_ptr_ shared_data_;
		CharT small_data_[SMALL_SIZE];
	};

	Allocator<CharT> allocator_;
	String_state state_;

  public:
	String_core()
	: data_{}, size_(0), state_(String_state::SSO) {}
	String_core(const CharT* string, size_t count) : size_(count) {
		if (!is_size_small())
			construct_dynamic(string);
		else
			construct_static(string);
	}

	String_core(size_t size, const CharT& init_element)
	: size_(size) {
		if (!is_size_small())
			construct_dynamic(init_element);
		else
			construct_static(init_element);
	}

	String_core(String_core& other, size_t pos = 0)
	: size_(other.size()) {
		if (other.is_static()) {
			construct_static(other.small_data_ + pos);
		} else if (other.is_dynamic()) {
			switch_to_other_owner(other);
		}
	}

	String_core(const String_core& other, size_t pos = 0)
	: size_(other.size()) {
		if (other.is_static())
			construct_static(other.small_data_ + pos);
		else
			construct_dynamic(other.data_.data_ + pos);
	}

	String_core(String_core&& other, size_t pos = 0)
	: size_(other.size()) {
		if (other.is_view()) {
			data_.data_ = other.data_.data_;
			data_.capacity_ = other.data_.capacity_;

			size_ = other.size_;
			state_ = String_state::VIEW;

			other.data_.data_ = nullptr;
			
			return;
		}

		if (!other.is_owner()) {
			shared_data_ = std::move(other.shared_data_);
			other.switch_to_static();
			size_ = 0;
			return;
		}

		if (other.is_static()) {
			construct_static(other.small_data_ + pos);
		} else {
			construct_dynamic(other.data_.data_ + pos);
			allocator_.deallocate(other.data_.data_);
		}
	}

	static String_core view(CharT** buffer, size_t count) {
		String_core result = {};

		result.data_.data_ = *buffer;
		result.data_.capacity_ = count;
		result.size_ = count;

		result.state_ = String_state::VIEW;

		return result;
	}

	~String_core() {
		if (is_dynamic()) {
			allocator_.deallocate(data_.data_);
			data_.capacity_ = 0;
		} else if (!is_owner()) {
			shared_data_.~Shared_ptr();
		}

		size_ = 0;
	}

	inline bool is_size_small() const {
		return size_ <= SMALL_SIZE;
	}

	inline bool is_size_small(size_t other_size) const {
		return other_size <= SMALL_SIZE;
	}

	inline bool is_static() const {
		return state_ == String_state::SSO;
	}

	inline bool is_dynamic() const {
		return state_ == String_state::DYNAMIC;
	}

	inline bool is_view() const {
		return state_ == String_state::VIEW;
	}

	inline bool is_owner() const {
		return state_ != String_state::NOT_OWNER;
	}

	size_t size() const {
		return size_;
	}

	size_t capacity() const {
		if (is_dynamic() || is_view()) {
			return data_.capacity_;
		}
		return SMALL_SIZE;
	}

	bool empty() const {
		return (size_ == 0);
	}

	CharT* data() {
		if (!is_owner())
			switch_to_owner();

		if (is_static())
			return small_data_;
		return data_.data_;
	}

	// const CharT* data() const {
	// 	if (is_dynamic())
	// 		return data_.data_;
	// 	return small_data_;
	// }
 
	CharT* c_str() const {
		if (is_dynamic() || is_view())
			return data_.data_;
		else
		if (is_static())
			return (CharT*)small_data_;
		return shared_data_->data_.data_;
	}

	String_core& operator=(const String_core& other) {
		if(!other.is_owner()) {
			share_to_other(other);
		} else {
			if(!is_owner())
				switch_to_owner();

			if (is_dynamic() && other.is_dynamic()) {
				// printf("dynamic & dynamic!\n");
				if (size_ < other.size())
					redistribute_memory(other.capacity());
			} else
			if (is_dynamic() && other.is_static()) {
				// printf("dynamic & static! (size %ld, other.size %ld)\n", size_, other.size());
				if (size_ < other.size())
					redistribute_memory(other.capacity());
			} else
			if (is_static() && other.is_dynamic()) {
				// printf("static & dynamic!\n");
				if (!is_size_small(other.size())) {
					switch_to_dynamic();
					redistribute_memory(other.capacity());
				}
			} else {
				// printf("static & static!\n");
			}
		}

		copy_data(other, other.size());

		return *this;
	}

	String_core& operator=(String_core&& other) {
		if (other.is_dynamic()) {
			if (is_dynamic())
				allocator_.deallocate(data_.data_);
			else
				switch_to_dynamic();

			data_.data_ = std::move(other.data_.data_);
			data_.capacity_ = other.capacity();

			size_ = other.size_;
		} else {
			if (is_dynamic())
				switch_to_static();
			memcpy(small_data_, other.small_data_, SMALL_SIZE);
		}

		return *this;
	}

	CharT& at(size_t index) {
		if (index >= size_)
			throw std::out_of_range(MESSAGE_BAD_INDEX);

		if (!is_owner())
			switch_to_owner();

		if (is_dynamic() || is_view())
			return data_.data_[index];
		else
		if (is_static())
			return small_data_[index];
		return shared_data_->data_.data_[index];
	}

	const CharT& at(size_t index) const {
		if (index >= size_)
			throw std::out_of_range(MESSAGE_BAD_INDEX);

		if (is_dynamic() || is_view())
			return data_.data_[index];
		return small_data_[index];
	}

	void push_back(CharT value) {
		if (is_static() && size_ + 1 > SMALL_SIZE)
			switch_to_dynamic();

		if (is_dynamic()) {
			if (size_ + 2 >= data_.capacity_)
				resize(data_.capacity_ * 2);

			data_.data_[size_] = value;
			data_.data_[size_ + 1] = CharT(0);
		} else {
			small_data_[size_] = value;
			small_data_[size_ + 1] = CharT(0);
		}

		++size_;
	}

	void pop_back() {
		--size_;

		if (is_dynamic()) {
			data_.data_[size_] = CharT(0);

			if (is_size_small())
				switch_to_static();
		}
		else
			small_data_[size_] = CharT(0);

		if (size_ * 4 < capacity() && !is_view())
			resize(capacity() / 2);
	}

	void resize(size_t new_capacity, CharT value = CharT()) {
		assert(!is_view());

		if (is_static()) {
			if (new_capacity > SMALL_SIZE)
				switch_to_dynamic();
			else
				throw std::runtime_error(MESSAGE_RESIZE_STATIC);
		} else {

			CharT* new_data = allocator_.allocate(new_capacity + 1);

			size_t copy_size = size_ < new_capacity ? size_ : new_capacity;
			for(size_t i = 0; i < copy_size; ++i)
				new_data[i] = data_.data_[i];

			if (copy_size < new_capacity)
				for(size_t i = size_; i < new_capacity; ++i)
					new_data[i] = value;

			size_ = copy_size;

			allocator_.deallocate(data_.data_);
			data_.data_ = new_data;
			data_.capacity_ = new_capacity + 1;
		}
	}

	void clear() {
		size_ = 0;
		switch_to_static();
	}

  protected:

	void redistribute_memory(size_t new_capacity) {
		assert(!is_view());

		if (!is_owner())
			switch_to_owner();

		if (new_capacity < capacity())
			return;

		if (is_static())
			switch_to_dynamic();

		++new_capacity;

		CharT* new_data = allocator_.allocate(new_capacity);

		for(size_t i = 0; i < size_; ++i)
			new_data[i] = data_.data_[i];

		if (data_.data_)
			allocator_.deallocate(data_.data_);

		data_.data_ = new_data;
		data_.capacity_ = new_capacity;
	}

  private:

	void construct_dynamic(const CharT* string) {
		size_t new_capacity = size_ * 2;
		CharT* new_data = allocator_.allocate(new_capacity);

		for(size_t i = 0; i < size_; ++i)
			new_data[i] = string[i];

		data_.data_ = new_data;
		data_.capacity_ = new_capacity;

		state_ = String_state::DYNAMIC;
	}

	void construct_dynamic(const CharT& value) {
		size_t new_capacity = size_ * 2;
		CharT* new_data = allocator_.allocate(new_capacity);

		for(size_t i = 0; i < size_; ++i)
			new_data[i] = value;

		data_.data_ = new_data;
		data_.capacity_ = new_capacity;

		state_ = String_state::DYNAMIC;
	}

	void construct_static(const CharT* string) {
		for(size_t i = 0; i < size_; ++i)
			small_data_[i] = string[i];

		state_ = String_state::SSO;
	}

	void construct_static(const CharT& value) {
		for(size_t i = 0; i < size_; ++i)
			small_data_[i] = value;

		state_ = String_state::SSO;
	}

	void share_to_other(const String_core& other) {
		shared_data_ = Shared_ptr_(other.shared_data_);
		size_ = other.size_;
		state_ = String_state::NOT_OWNER;
	}

	void switch_to_dynamic() {
		if (state_ == String_state::DYNAMIC)
			return;

		size_t new_capacity = size_ * 2;
		CharT* new_data = allocator_.allocate(new_capacity);

		for(size_t i = 0; i < size_; ++i)
			new_data[i] = small_data_[i];

		data_.data_ = new_data;
		data_.capacity_ = new_capacity;

		state_ = String_state::DYNAMIC;
	}

	void switch_to_static() {
		if (state_ == String_state::SSO || !is_size_small())
			return;

		CharT copy_static[SMALL_SIZE];

		for(size_t i = 0; i < size_; ++i)
			copy_static[i] = data_.data_[i];

		allocator_.deallocate(data_.data_);

		for(size_t i = 0; i < size_; ++i)
			small_data_[i] = copy_static[i];
		
		state_ = String_state::SSO;
	}

	void switch_to_owner() {
		if (shared_data_->is_dynamic()) {
			CharT* cow_data = shared_data_->data_.data_;

			shared_data_.~Shared_ptr();

			switch_to_dynamic();

			data_.data_ = allocator_.allocate(size_ * 2);
			copy_data(cow_data, size_);

			data_.capacity_ = size_ * 2;
		} else {
			CharT tmp_buffer[SMALL_SIZE];
			memcpy(tmp_buffer, shared_data_->small_data_, SMALL_SIZE);

			shared_data_.~Shared_ptr();

			switch_to_static();
			copy_data(tmp_buffer, size_);
		}
	}

	void switch_to_other_owner(String_core& other) {
		other.switch_to_non_owner();
		shared_data_ = Shared_ptr_(other.shared_data_);
		size_ = other.size_;
		state_ = String_state::NOT_OWNER;
	}

	void switch_to_non_owner() {
		Shared_ptr_ new_ptr(this);
		shared_data_ = std::move(new_ptr);
		state_ = String_state::NOT_OWNER;
	}

	void copy_data(const String_core& string, size_t length) {
		copy_data(string.c_str(), length);
	}

	void copy_data(const CharT* string, size_t length) {
		// assert(!(other.is_static() && length > SMALL_SIZE));

		if (is_dynamic()) {
			assert(capacity() > length);

			for (size_t i = 0; i < length; ++i)
				data_.data_[i] = string[i];
		} else {
			for (size_t i = 0; i < length; ++i)
				small_data_[i] = string[i];
		}

		// if (is_dynamic() && other.is_dynamic()) {
		// 	for(size_t i = 0; i < length; ++i)
		// 		data_.data_[i] = other.data_.data_[i];
		// 	data_.capacity_ = length * 2;
		// } else
		// if (is_static() && other.is_static())
		// 	for(size_t i = 0; i < length; ++i)
		// 		small_data_[i] = other.small_data_[i];
		// else
		// if (is_dynamic() && other.is_static()) {
		// 	for(size_t i = 0; i < length; ++i)
		// 		data_.data_[i] = other.small_data_[i];
		// 	data_.capacity_ = length * 2;
		// } else
		// if (is_static() && other.is_dynamic()) {
		// 	for(size_t i = 0; i < length; ++i)
		// 		small_data_[i] = other.data_.data_[i];
		// }

		size_ = length;

		// if (is_size_small())
		// 	switch_to_static();
	}
};

#endif