#ifndef DYNAMIC_MEM_H
#define DYNAMIC_MEM_H

#include <cstddef>
#include <cstdlib>
#include <cassert>

template <typename T>
class Dynamic_storage {
  public:
	// ------------------------------------------------------------------------
	// -------------------- for dynamic storage  ------------------------------
  protected:
	T* data_;
	size_t size_;
	size_t capacity_;

  public:

	Dynamic_storage() : size_(0), capacity_(0), data_(nullptr) {}

	Dynamic_storage(size_t size, const T& init_element) : size_(size), capacity_(size * 2) {
		data_ = (T*)(new unsigned char[capacity_ * sizeof(T)]);
		if(data_ == nullptr)
			throw std::bad_alloc();

		for (size_t i = 0; i < size_; ++i)
			new(data_ + i) T(init_element);
	}

	Dynamic_storage(std::initializer_list<T> list): size_(list.size()),
					capacity_(list.size() * 2) {
		data_ = (T*)(new unsigned char[size_ * sizeof(T)]);
		if(data_ == nullptr)
			throw std::bad_alloc();

		size_t index = 0;
		for (auto i = list.begin(); i != list.end(); ++i) {
			new(data_ + index) T(*i);
			++index;
		}
	}

	~Dynamic_storage() {
		for(size_t i = 0; i < size_; ++i)
			data_[i].~T();

		size_ = capacity_ = 0;
		delete[] data_;
	}

	// ------------------------------------------------------------------------
	// -------------------- api dynamic storage  ------------------------------	

	T& data(size_t index) {
		if(index > size_)
			throw std::out_of_range(MESSAGE_BAD_INDEX);

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
			data_[i].~T();
		}

		size_ = 0;
	}

	void resize(size_t new_size) {
		T* new_data = (T*)(new unsigned char[new_size * sizeof(T)]);

		size_ = (new_size > size_ ? size_ : new_size);
		for(size_t i = 0; i < size_; ++i) {
			new_data[i] = data_[i];
		}

		delete[] data_;

		data_ = new_data;
		capacity_ = new_size;
	}

	void resize(size_t new_size, const T& initializer_value) {
		T* new_data = (T*)(new unsigned char[new_size * sizeof(T)]);

		size_ = (new_size > size_ ? size_ : new_size);
		for(int i = 0; i < size_; ++i) {
			new_data[i] = data_[i];
		}

		for(int i = size_; i < capacity_; ++i)
			new(new_data + i) T(initializer_value);

		delete[] data_;

		data_ = new_data;
		capacity_ = new_size;
	}

	void push_back(const T& value) {
		if(size_ + 1 >= capacity_)
			resize(capacity_ * 2);

		new(data_ + size_) T(value);
		++size_;
	}

	void push_back(T&& value) {
		if(size_ + 1 >= capacity_)
			resize(capacity_ * 2);

		new(data_ + size_) T(std::move(value));
		++size_;
	}

	template<class... Args> 
	void emplace_back(Args&&... args) {
		if(size_ + 1 >= capacity_)
			resize(capacity_ * 2);

		new(data_ + size_) T(std::forward<Args>(args)...);
		++size_;
	}

	T pop_back() {
		T tail = data_[size_];

		data_[size_--].~T();

		return tail;
	}

	T get_element(size_t index) {
		assert(index < size_);

		return data_[index];
	}
};

#endif
