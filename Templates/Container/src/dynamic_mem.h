#ifndef DYNAMIC_MEM_H
#define DYNAMIC_MEM_H

#include <cstddef>
#include <cstdlib>
#include <cassert>
#include "allocator.h"

template <typename T, template <typename U> typename Allocator>
class Dynamic_storage {
  public:
	// ------------------------------------------------------------------------
	// -------------------- for dynamic storage  ------------------------------
  protected:
	T* data_;
	size_t size_;
	size_t capacity_;

	Allocator<T> allocator_;

  public:

	Dynamic_storage() : size_(0), capacity_(0), data_(nullptr) {}

	Dynamic_storage(size_t size, const T& init_element) : size_(size), capacity_(size * 2) {
		// printf("INIT DYNAMIC_MEM\n");
		data_ = allocator_.allocate(capacity_);
		if(data_ == nullptr)
			throw std::bad_alloc();

		for (size_t i = 0; i < size_; ++i)
			allocator_.construct(data_ + i, init_element); // new(data_ + i) T(init_element);
	}

	Dynamic_storage(std::initializer_list<T> list): size_(list.size()),
					capacity_(list.size() * 2) {
		data_ = allocator_.allocate(size_);
		if(data_ == nullptr)
			throw std::bad_alloc();

		size_t index = 0;
		for (auto i = list.begin(); i != list.end(); ++i) {
			allocator_.construct(data_ + index, *i); // new(data_ + index) T(*i);
			++index;
		}
	}

	~Dynamic_storage() {
		for(size_t i = 0; i < size_; ++i)
			allocator_.destroy(data_ + i); // data_[i].~T();

		size_ = capacity_ = 0;
		allocator_.deallocate(data_);
	}

	// ------------------------------------------------------------------------
	// -------------------- api dynamic storage  ------------------------------	

	T& data(size_t index) {
		if(index > size_)
			throw std::out_of_range(MESSAGE_BAD_INDEX);

		if(!data_)
			data_ = allocator_.allocate(capacity_); // (T*)new char[capacity_ * sizeof(T)];

		return data_[index];
	}

	size_t size() const {
		return size_;
	}

	size_t capacity() const {
		return capacity_;
	}

	void clear() {
		for(size_t i = 0; i < size_; ++i) {
			allocator_.destroy(data_ + i); // data_[i].~T();
		}

		size_ = 0;
	}

	void resize(size_t new_size) {
		size_t new_capacity = new_size * 2;
		T* new_data = allocator_.allocate(new_capacity); // (T*)(new char[new_capacity * sizeof(T)]);

		size_t min_size = (new_size > size_ ? size_ : new_size);
		for(size_t i = 0; i < min_size; ++i) {
			allocator_.construct(new_data + i, std::move(data_[i])); // new(new_data + i) T(std::move(data_[i]));
		}

		if(new_size < size_)
			for(size_t i = size_; i < new_size; ++i)
				allocator_.destroy(data_ + i); // data_[i].~T();

		// delete[] data_;
		allocator_.deallocate(data_);

		data_ = new_data;
		capacity_ = new_capacity;
		size_ = new_size;
	}

	void resize(size_t new_size, const T& initializer_value) {
		size_t new_capacity = new_size * 2;
		T* new_data = allocator_.allocate(new_capacity); // (T*)(new char[new_capacity * sizeof(T)]);

		size_t min_size_ = (new_size > size_ ? size_ : new_size);
		for(int i = 0; i < min_size_; ++i) {
			allocator_.construct(new_data + i, std::move(data_[i])); // new(new_data + i) T(std::move(data_[i]));
		}

		for(int i = min_size_; i < new_size; ++i)
			allocator_.construct(new_data + i, initializer_value); // new(new_data + i) T(initializer_value);

		if(new_size < size_)
			for(size_t i = size_; i < min_size_; ++i)
				allocator_.destroy(data_ + i); // data_[i].~T();

		allocator_.deallocate(data_); // delete[] data_;

		data_ = new_data;
		capacity_ = new_capacity;
		size_ = new_size;
	}

	void push_back(const T& value) {
		if(size_ + 1 >= capacity_)
			resize(capacity_ * 2);

		allocator_.construct(data_ + size_, value); // new(data_ + size_) T(value);
		++size_;
	}

	void push_back(T&& value) {
		if(size_ + 1 >= capacity_)
			resize(capacity_ * 2);

		allocator_.construct(data_ + size_, std::move(value)); // new(data_ + size_) T(std::move(value));
		++size_;
	}

	template<class... Args> 
	void emplace_back(Args&&... args) {
		if(size_ + 1 >= capacity_)
			resize(capacity_ * 2);

		allocator_.construct(data_ + size_, std::forward<Args>(args)...); // new(data_ + size_) T(std::forward<Args>(args)...);
		++size_;
	}

	T pop_back() {
		T tail = data_[size_];

		allocator_.destroy(data_ + size_); // data_[size_--].~T();
		--size_;

		return tail;
	}
};

#endif
