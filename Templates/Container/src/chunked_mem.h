#ifndef CHUNKED_MEM_H
#define CHUNKED_MEM_H

#include <cstddef>
#include <cstdlib>
#include <cassert>

template <typename T>
struct init_element_info {
	bool is_used;
	T element;

	init_element_info(bool arg_is_used) : is_used(arg_is_used) {}
	init_element_info(bool arg_is_used, const T& arg_element) : is_used(arg_is_used), element(arg_element) {}
};

template <typename T, size_t arg_chunk_size>
class Chunked_storage_ {
  protected:
	T** data_;
	size_t chunk_size_;
	size_t size_;
	size_t capacity_;
	init_element_info<T> init_element_info_;

	Allocator<T> allocator_;
	Allocator<T*> ptr_allocator_;

  public:

	Chunked_storage_() : data_(nullptr), chunk_size_(arg_chunk_size),
						size_(0),
						capacity_(0),
						init_element_info_(false) {}

	Chunked_storage_(size_t data_size, const T& init_element):
					data_(nullptr), chunk_size_(arg_chunk_size), size_(data_size),
					capacity_(2 * (size_ / chunk_size_ + ((size_ % chunk_size_) != 0))),
					init_element_info_(true, init_element) {}

	Chunked_storage_(std::initializer_list<T> list):
					chunk_size_(arg_chunk_size), size_(list.size()),
					capacity_(2 * (size_ / chunk_size_ + ((size_ % chunk_size_) != 0))),
					init_element_info_(false) {
		size_t chunk_count = size_ / chunk_size_ + ((size_ % chunk_size_) != 0);
		data_ = ptr_allocator_.allocate(chunk_count); // new T*[chunk_count];

		size_t index = 0;
		for (auto i = list.begin(); i != list.end(); ++i) {
			if(index % chunk_size_ == 0)
				data_[index / chunk_size_] = allocator_.allocate(chunk_size_); // (T*)(new char[chunk_size_ * sizeof(T)]);

			allocator_.construct(data_[index / chunk_size_] + index % chunk_size_, *i); // new(data_[index / chunk_size_] + index % chunk_size_) T(*i);
			++index;
		}
	}

	~Chunked_storage_() {
		size_t chunk_count = size_ / chunk_size_ + ((size_ % chunk_size_) != 0);

		for(int i = 0; i < chunk_count; ++i) {
			if(data_[i]) {
				for(int j = 0; j < chunk_size_; ++j)
					allocator_.destroy(data_[i] + j); // data_[i][j].~T();
				allocator_.deallocate(data_[i]);
			}
		}

		size_ 		= 0;
		capacity_ 	= 0;
		chunk_size_ = 0;

		ptr_allocator_.deallocate(data_);
	}
	
	// ------------------------------------------------------------------------
	// -------------------- api dynamic storage  ------------------------------	

	T& data(size_t index) {
		if(index >= size_)
			throw std::out_of_range(MESSAGE_BAD_INDEX);

		size_t chunk_count = index / chunk_size_;
		if(!data_) {
			data_ = ptr_allocator_.allocate(capacity_); // new T*[capacity_];
			for(size_t i = 0; i < capacity_; ++i)
				data_[i] = nullptr;
		}

		if(!data_[chunk_count]) {
			data_[chunk_count] = allocator_.allocate(chunk_size_); // (T*)(new char[chunk_size_ * sizeof(T)]);

			if(init_element_info_.is_used) {
				for(size_t i = 0; i < chunk_size_; ++i)
					allocator_.construct(data_[chunk_count] + i, init_element_info_.element); // new(data_[chunk_count] + i) T(init_element_info_.element);
			}
		}

		return data_[chunk_count][index % chunk_size_];
	}

	size_t size() const {
		return size_;
	}

	size_t capacity() const {
		return capacity_;
	}

	size_t chunk_size() const {
		return chunk_size_;
	}

	void clear() {
		size_t chunk_count = size_ / chunk_size_ + ((size_ % chunk_size_) != 0);

		for(int i = 0; i < chunk_count; ++i) {
			if(data_[i])
				for(int j = 0; j < chunk_size_; ++j)
					allocator_.destroy(data_[i] + j); // data_[i][j].~T();
		}

		size_ = 0;
	}

	void resize(size_t new_size) {
		size_t new_capacity = new_size / chunk_size_ + ((new_size % chunk_size_) != 0);
		size_t min_capacity = (new_capacity > capacity_ ? capacity_ : new_capacity);

		// printf("new_size %ld, new_capacity %ld, chunk_size %ld\n", new_size, new_capacity, chunk_size_);
		T** new_data = ptr_allocator_.allocate(new_capacity); // new T*[new_capacity];
		memset(new_data, 0, new_capacity);

		size_t min_size_ = (new_size > size_ ? size_ : new_size);

		for(size_t i = 0; i < min_capacity; ++i) {
			if(data_[i]) {
				new_data[i] = data_[i];
			} else if(init_element_info_.is_used) {
				for(size_t j = 0; j < chunk_size_; ++j)
					allocator_.construct(new_data[i] + j, init_element_info_.element);
					// new(new_data[i] + j) T(init_element_info_.element);
			}
		}

		if(new_size < size_)
			for(size_t i = min_size_; i < size_; ++i)
				data_[i / chunk_size_][i % chunk_size_].~T();

		// delete[] data_;
		ptr_allocator_.deallocate(data_);

		data_ = new_data;
		capacity_ = new_capacity;

		if(new_size < size_)
			size_ = new_size;
	}

	void resize(size_t new_size, const T& init_value) {
		size_t new_capacity = new_size / chunk_size_ + ((new_size % chunk_size_) != 0);
		size_t min_capacity = (new_capacity > capacity_ ? capacity_ : new_capacity);

		// printf("new_size %ld, new_capacity %ld, chunk_size %ld\n", new_size, new_capacity, chunk_size_);
		T** new_data = ptr_allocator_.allocate(new_capacity); // new T*[new_capacity];
		memset(new_data, 0, new_capacity);

		size_t min_size_ = (new_size > size_ ? size_ : new_size);

		for(size_t i = 0; i < min_capacity; ++i) {
			if(data_[i]) {
				new_data[i] = data_[i];
			} else if(init_element_info_.is_used) {
				for(size_t j = 0; j < chunk_size_; ++j)
					allocator_.construct(new_data[i] + j, init_element_info_.element);
					// new(new_data[i] + j) T(init_element_info_.element);
			}
		}

		if(new_size < size_)
			for(size_t i = min_size_; i < size_; ++i)
				allocator_.destroy(data_[i / chunk_size_] + i % chunk_size_);
				// data_[i / chunk_size_][i % chunk_size_].~T();

		// delete[] data_;
		ptr_allocator_.deallocate(data_);

		if(new_size > size_)
			for(size_t i = min_size_; i < size_; ++i)
				allocator_.construct(new_data[i / chunk_size_] + i % chunk_size_, init_value);
				// new(new_data[i / chunk_size_] + i % chunk_size_) T(init_value);

		data_ = new_data;
		capacity_ = new_capacity;
		init_element_info_.is_used = true;
		init_element_info_.element = init_value;

		if(new_size < size_)
			size_ = new_size;
	}	

	void push_back(const T& value) {
		if(size_ >= capacity_ * chunk_size_)
			resize(capacity_ * 2 * chunk_size_);

		size_t chunk_count = size_ / chunk_size_;
		if(!data_) {
			data_ = ptr_allocator_.allocate(capacity_); // new T*[capacity_];
		}

		if(!data_[chunk_count]) {
			data_[chunk_count] = allocator_.allocate(chunk_size_); // (T*)(new char[chunk_size_ * sizeof(T)]);

			size_t remainder = size_ % chunk_size_;
			if(remainder != 0 && init_element_info_.is_used)
				for(size_t i = 0; i < remainder; ++i)
					allocator_.construct(data_[chunk_count] + i, init_element_info_.element);
					// new(data_[chunk_count] + i) T(init_element_info_.element);
		}

		// new(data_[chunk_count] + size_ % chunk_size_) T(value);
		allocator_.construct(data_[chunk_count] + size_ % chunk_size_, value);
		++size_;
	}

	void push_back(T&& value) {
		if(size_ >= capacity_ * chunk_size_)
			resize(capacity_ * 2 * chunk_size_);

		size_t chunk_count = size_ / chunk_size_;

		if(!data_) {
			data_ = ptr_allocator_.allocate(capacity_); // new T*[capacity_];
			memset(data_, 0, capacity_);
		}

		if(!data_[chunk_count]) {
			data_[chunk_count] = allocator_.allocate(chunk_size_); // (T*)(new char[chunk_size_ * sizeof(T)]);
			if(init_element_info_.is_used) {
				size_t pos = size_ % chunk_size_;
				for(size_t i = 0; i < pos; ++i)
					allocator_.construct(data_[size_ / chunk_size_] + pos, init_element_info_.element);
					// new(data_[size_ / chunk_size_] + pos) T(init_element_info_.element);
			}
		}

		// new(data_[chunk_count] + size_ % chunk_size_) T(std::move(value));
		allocator_.construct(data_[chunk_count] + size_ % chunk_size_, std::move(value));
		++size_;
	}

	template<class... Args> 
	void emplace_back(Args&&... args) {
		if(size_ >= capacity_ * chunk_size_)
			resize(capacity_ * 2 * chunk_size_);

		size_t chunk_count = size_ / chunk_size_;

		if(!data_) {
			data_ = ptr_allocator_.allocate(capacity_); // new T*[capacity_];
			memset(data_, 0, capacity_);
		}

		if(!data_[chunk_count]) {
			data_[chunk_count] =  allocator_.allocate(chunk_size_); // (T*)(new char[chunk_size_ * sizeof(T)]);
		}

		// new(data_[chunk_count] + size_ % chunk_size_) T(std::forward<Args>(args)...);
		allocator_.construct(data_[chunk_count] + size_ % chunk_size_, std::forward<Args>(args)...);
		++size_;
	}

	T pop_back() {
		if(size_ == 0)
			throw std::out_of_range(MESSAGE_DATA_IS_EMPTY);

		T value = {};

		if(size_ % chunk_size_ == 0) {
			value = data_[size_ / chunk_size_ - 1][chunk_size_ - 1];
			allocator_.destroy(data_[size_ / chunk_size_ - 1] + chunk_size_ - 1);
			// data_[size_ / chunk_size_ - 1][chunk_size_ - 1].~T();
		}
		else {
			value = data_[size_ / chunk_size_][size_ % chunk_size_ - 1];
			allocator_.destroy(data_[size_ / chunk_size_] + size_ % chunk_size_ - 1);
			// data_[size_ / chunk_size_][size_ % chunk_size_ - 1].~T();
		}

		--size_;
		return value;
	}
};

template <size_t chunk_size>
struct Chunked_storage {
  public:
	template <typename T>
	using type = Chunked_storage_<T, chunk_size>;
};


#endif
