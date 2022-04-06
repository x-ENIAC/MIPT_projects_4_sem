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
	// ------------------------------- iterator -------------------------------
	class Iterator {
	  private:
		T* pointer_;

	  public:
		Iterator(): pointer_(nullptr) {}
		Iterator(T* pointer): pointer_(pointer) {}

		T& operator*() const {
			return *pointer_;
		}

		T* operator->() const {
			return pointer_;
		}

		bool operator!=(const Iterator& another_iterator) const {
			return this->pointer_ != another_iterator.pointer_;
		}

		bool operator==(const T& another_iterator) {
			return this->pointer_ == another_iterator.pointer_;
		}

		Iterator& operator++() { // prefix
			++pointer_;
			return *this;
		}

		Iterator& operator--() { // prefix
			--pointer_;
			return *this;
		}		
	};

	// ------------------------------------------------------------------------
	// ----------------------------- reverse iterator -------------------------
	class Reverse_iterator {
	  private:
		T* pointer_;

	  public:
		Reverse_iterator(): pointer_(nullptr) {}
		Reverse_iterator(T* pointer): pointer_(pointer) {}

		T& operator*() const {
			return *pointer_;
		}

		T* operator->() const {
			return pointer_;
		}

		bool operator!=(const Reverse_iterator& another_reverse_iterator) const {
			return this->pointer_ != another_reverse_iterator.pointer_;
		}

		bool operator==(const T& another_reverse_iterator) {
			return this->pointer_ == another_reverse_iterator.pointer_;
		}

		Reverse_iterator& operator++() { // prefix
			--pointer_;
			return *this;
		}

		Reverse_iterator& operator--() { // prefix
			++pointer_;
			return *this;
		}		
	};	

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

	Iterator begin() {
		if(size_ == 0)
			throw std::out_of_range(MESSAGE_DATA_IS_EMPTY);
		return Iterator(&Storage<T, size>::data_[0]);
	}

	Iterator end() {
		if(size_ == 0)
			throw std::out_of_range(MESSAGE_DATA_IS_EMPTY);
		return Iterator(&Storage<T, size>::data_[size_]);
	}

	Reverse_iterator rbegin() {
		if(size_ == 0)
			throw std::out_of_range(MESSAGE_DATA_IS_EMPTY);
		return Reverse_iterator(&Storage<T, size>::data_[size_ - 1]);
	}

	Reverse_iterator rend() {
		if(size_ == 0)
			throw std::out_of_range(MESSAGE_DATA_IS_EMPTY);
		return Reverse_iterator(&Storage<T, size>::data_[0] - 1);
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