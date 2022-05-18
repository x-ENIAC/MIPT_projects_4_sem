#ifndef STRING_STORAGE_H
#define STRING_STORAGE_H

#include <cstddef>
#include <cstdlib>
#include <cassert>
#include "allocator.h"
#include "error_codes.h"

const size_t SMALL_SIZE = 8;

enum class String_state {
	SSO				= 1,
	DYNAMIC			= 2,
	VIEW			= 3
};

template < typename CharT >
class String_storage {
  private:
	size_t size_;

	struct Dynamic_data {
		CharT* data_;
		size_t capacity_;
	};

	union {
		Dynamic_data data_;
		CharT small_data_[SMALL_SIZE];
	};

	Allocator<CharT> allocator_;
	String_state state_;

  public:
	String_storage() : data_{}, size_(0), state_(String_state::SSO) {}
	String_storage(const CharT* string, size_t count) : size_(count) {
		if(!is_size_small())
			construct_dynamic(string);
		else
			construct_static(string);
	}

	String_storage(size_t size, const CharT& init_element) : size_(size) {
		if(!is_size_small())
			construct_dynamic(init_element);
		else
			construct_static(init_element);
	}

	String_storage(const String_storage& other, size_t pos = 0) : size_(other.size()) {
		if(other.is_size_small())
			construct_static(other.small_data_ + pos);
		else
			construct_dynamic(other.data_.data_ + pos);
	}

	String_storage(String_storage&& other, size_t pos = 0) : size_(other.size()) {
		if(other.is_view()) {
			data_.data_ = other.data_.data_;
			data_.capacity_ = other.data_.capacity_;

			size_ = other.size_;
			state_ = String_state::VIEW;

			other.data_.data_ = nullptr;
			
			return;
		}

		if(other.is_size_small())
			construct_static(other.small_data_ + pos);
		else
			construct_dynamic(other.data_.data_ + pos);
	}

	static String_storage view(CharT** buffer, size_t count) {
		String_storage result = {};

		result.data_.data_ = *buffer;
		result.data_.capacity_ = count;
		result.size_ = count;

		result.state_ = String_state::VIEW;

		return result;
	}

	~String_storage() {
		if(is_dynamic()) {
			allocator_.deallocate(data_.data_);
			data_.capacity_ = 0;
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

	size_t size() const {
		return size_;
	}

	size_t capacity() const {
		if(is_dynamic() || is_view()) {
			return data_.capacity_;
		}
		return SMALL_SIZE;
	}

	bool empty() const {
		return (size_ == 0);
	}

	CharT* data() {
		if(is_dynamic())
			return data_.data_;
		return small_data_;
	}

	const CharT* data() const {
		if(is_dynamic())
			return data_.data_;
		return small_data_;
	}
 
	CharT* c_str() const {
		if(is_dynamic() || is_view())
			return data_.data_;
		return (CharT*)small_data_;
	}

	String_storage& operator=(const String_storage& other) {
		if(is_dynamic() && other.is_dynamic()) {
			// printf("dynamic & dynamic!\n");
			if(size_ < other.size())
				redistribute_memory(other.capacity());
		} else
		if(is_dynamic() && other.is_static()) {
			// printf("dynamic & static! (size %ld, other.size %ld)\n", size_, other.size());
			if(size_ < other.size())
				redistribute_memory(other.capacity());
		} else
		if(is_static() && other.is_dynamic()) {
			// printf("static & dynamic!\n");
			if(!is_size_small(other.size())) {
				switch_to_dynamic();
				redistribute_memory(other.capacity());
			}
		} else {
			// printf("static & static!\n");
		}

		copy_data(other, other.size());

		return *this;
	}

	String_storage& operator=(String_storage&& other) {
		if(other.is_dynamic()) {
			if(is_dynamic())
				allocator_.deallocate(data_.data_);
			else
				switch_to_dynamic();

			data_.data_ = std::move(other.data_.data_);
			data_.capacity_ = other.capacity();

			size_ = other.size_;
		} else {
			if(is_dynamic())
				switch_to_static();
			memcpy(small_data_, other.small_data_, SMALL_SIZE);
		}

		return *this;
	}

	CharT& at(size_t index) {
		if(index >= size_)
			throw std::out_of_range(MESSAGE_BAD_INDEX);

		if(is_dynamic() || is_view())
			return data_.data_[index];
		return small_data_[index];
	}

	const CharT& at(size_t index) const {
		if(index >= size_)
			throw std::out_of_range(MESSAGE_BAD_INDEX);

		if(is_dynamic() || is_view())
			return data_.data_[index];
		return small_data_[index];
	}

	void push_back(CharT value) {
		if(is_static() && size_ + 1 > SMALL_SIZE)
			switch_to_dynamic();

		if(is_dynamic()) {
			if(size_ + 2 >= data_.capacity_)
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

		if(is_dynamic()) {
			data_.data_[size_] = CharT(0);

			if(is_size_small())
				switch_to_static();
		}
		else
			small_data_[size_] = CharT(0);

		if(size_ * 4 < capacity() && !is_view())
			resize(capacity() / 2);
	}

	void resize(size_t new_capacity, CharT value = CharT()) {
		assert(!is_view());

		if(is_static()) {
			if(new_capacity > SMALL_SIZE)
				switch_to_dynamic();
			else
				throw std::runtime_error(MESSAGE_RESIZE_STATIC);
		} else {

			CharT* new_data = allocator_.allocate(new_capacity + 1);

			size_t copy_size = size_ < new_capacity ? size_ : new_capacity;
			for(size_t i = 0; i < copy_size; ++i)
				new_data[i] = data_.data_[i];

			if(copy_size < new_capacity)
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

		if(new_capacity < capacity())
			return;

		if(is_static())
			switch_to_dynamic();

		++new_capacity;

		CharT* new_data = allocator_.allocate(new_capacity);

		for(size_t i = 0; i < size_; ++i)
			new_data[i] = data_.data_[i];

		if(data_.data_)
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

	void switch_to_dynamic() {
		if(state_ == String_state::DYNAMIC)
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
		if(state_ == String_state::SSO || !is_size_small())
			return;

		CharT copy_static[SMALL_SIZE];

		for(size_t i = 0; i < size_; ++i)
			copy_static[i] = data_.data_[i];

		allocator_.deallocate(data_.data_);

		for(size_t i = 0; i < size_; ++i)
			small_data_[i] = copy_static[i];
		
		state_ = String_state::SSO;
	}

	void copy_data(const String_storage& other, size_t length) {
		assert(!(other.is_static() && length > SMALL_SIZE));

		if(is_dynamic() && other.is_dynamic()) {
			for(size_t i = 0; i < length; ++i)
				data_.data_[i] = other.data_.data_[i];
			data_.capacity_ = length * 2;
		} else
		if(is_static() && other.is_static())
			for(size_t i = 0; i < length; ++i)
				small_data_[i] = other.small_data_[i];
		else
		if(is_dynamic() && other.is_static()) {
			for(size_t i = 0; i < length; ++i)
				data_.data_[i] = other.small_data_[i];
			data_.capacity_ = length * 2;
		} else
		if(is_static() && other.is_dynamic()) {
			for(size_t i = 0; i < length; ++i)
				small_data_[i] = other.data_.data_[i];
		}

		size_ = length;

		if(is_size_small())
			switch_to_static();
	}
};

#endif