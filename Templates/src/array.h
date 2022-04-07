#ifndef ARRAY_H
#define ARRAY_H

#include "static_mem.h"
#include "dynamic_mem.h"

template <
	typename T,
	size_t size,
	template <typename storage_type, size_t storage_size> typename Storage
	>
class Array: public Storage<T, size> {
  private:
	using Storage<T, size>::size_;

  public:
	// ------------------------------------------------------------------------
	// ----------------------------- array ------------------------------------
	Array(): Storage<T, size>() {}
	Array(const T& init_element): Storage<T, size>(init_element) {}
	Array(std::initializer_list<T> list): Storage<T, size>(list) {}

	T& operator[](size_t index) {
		if(index > size_)
			throw std::out_of_range(MESSAGE_BAD_INDEX);
		return Storage<T, size>::data_[index];
	}

	T& front() {
		if(size_ == 0)
			throw std::out_of_range(MESSAGE_DATA_IS_EMPTY);
		return Storage<T, size>::data_[0];
	}

	T& back() {
		if(size_ == 0)
			throw std::out_of_range(MESSAGE_DATA_IS_EMPTY);
		return Storage<T, size>::data_[size_];
	}
};

// -------------------------------------------------------------------

// template <
// 	size_t size,
// 	template <typename storage_type, size_t storage_size> typename Storage
// 	>
// class Array: public Storage<bool, size> {
//   public:

// 	T& operator[](size_t index) {
// 		return data(index);
// 	}

// private:
// 	Storage<T, size> data;
// };

#endif