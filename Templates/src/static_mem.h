#ifndef STATIC_MEM_H
#define STATIC_MEM_H

#include "error_codes.h"


template <typename T, size_t data_size>
class Static_storage_ {
  protected:
	T data_[data_size];
	const size_t size_;

  public:

	Static_storage_(): size_(data_size) {}

	Static_storage_(std::initializer_list<T> list): size_(data_size) {
		if (list.size() > size_) 
			throw std::out_of_range(MESSAGE_WRONG_INIT_LIST_SIZE);
			   
		size_t index = 0;
		for (auto i = list.begin(); i != list.end(); ++i) {
			data_[index] = *i;
			++index;
		}
	}

	~Static_storage_() {
		for(int i = 0; i < size_; ++i)
			data_[i].~T();
	}

	T& data(size_t index) {
		if(index > size_)
			throw std::out_of_range(MESSAGE_BAD_INDEX);

		return data_[index];
	}

	size_t size() const {
		return size_;
	}

	void clear() {
		throw std::runtime_error(MESSAGE_CLEAR_STATIC);
	}

	void resize(size_t new_size) {
		throw std::runtime_error(MESSAGE_RESIZE_STATIC);
	}

	void resize(size_t new_size, const T& initializer_value) {
		throw std::runtime_error(MESSAGE_RESIZE_STATIC);
	}

	// using type = Static_storage_<T, data_size>;
};

template <size_t data_size>
struct Static_storage {
  public:
	template <typename T>
	using type = Static_storage_<T, data_size>;
};

#endif