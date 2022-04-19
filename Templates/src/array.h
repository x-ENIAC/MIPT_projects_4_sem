#ifndef ARRAY_H
#define ARRAY_H

#include "static_mem.h"
#include "dynamic_mem.h"

template <
	typename T,
	template <typename storage_type> typename Storage
	>
class Array: public Storage<T> {
  private:
	typedef Storage<T> Storage_;

  public:
	// ------------------------------------------------------------------------
	// ----------------------------- array ------------------------------------
	Array(): Storage_() {}
	Array(size_t size, const T& init_element): Storage_(size, init_element) {}
	Array(std::initializer_list<T> list): Storage_(list) {}

	T& operator[](size_t index) {
		if(index > Storage_::size_)
			throw std::out_of_range(MESSAGE_BAD_INDEX);
		return Storage_::data(index);
	}

	T& front() {
		if(Storage_::size_ == 0)
			throw std::out_of_range(MESSAGE_DATA_IS_EMPTY);
		return Storage_::data_[0];
	}

	T& back() {
		if(Storage_::size_ == 0)
			throw std::out_of_range(MESSAGE_DATA_IS_EMPTY);
		return Storage_::data_[Storage_::size_];
	}

	template < typename Iterator_type, typename Container >
	class Iterator {
	  private:
		Container* container_;
		int index_;

	  public:
		using difference_type	= ptrdiff_t;
		using value_type		= Iterator_type;
		using pointer			= Iterator_type*;
		using reference			= Iterator_type&;
		using iterator_category	= std::forward_iterator_tag;

		Iterator(): container_(nullptr), index_(0) {}
		Iterator(Container* container, const int index): container_(container), index_(index) {}
		Iterator(const Iterator& other) {
			container_ = other.container_;
			index_ = other.index_;
		}

		Iterator_type& operator*() const {
			return (*container_)[index_];
		}

		Iterator_type* operator->() const {
			return &container_[0] + index_;
		}

		bool operator==(const Iterator<Iterator_type, Container> &other) const {
			return index_ == other.index_;
		}

		bool operator!=(const Iterator<Iterator_type, Container> &other) const {
			return index_ != other.index_;
		}

		Iterator& operator++() {
			++index_;
			return *this;
		}

		Iterator& operator++(int tmp) {
			Iterator copy_this(*this);
			++index_;
			return copy_this;
		}

		Iterator& operator--() {
			--index_;
			return *this;
		}

		Iterator& operator--(int tmp) {
			Iterator copy_this(*this);
			--index_;
			return copy_this;
		}		
	};

	using iterator = Iterator<T, Array>;
	using reverse_iterator = std::reverse_iterator<Iterator<T, Array>>;
	using const_iterator = Iterator<T, const Array>;

	// ------------------------------------------------------------------------
	// ------------------------ for iterator  ---------------------------------
	iterator begin() {
		if(Storage_::size_ == 0)
			throw std::out_of_range(MESSAGE_DATA_IS_EMPTY);
		return iterator(this, 0);
	}

	iterator end() {
		if(Storage_::size_ == 0)
			throw std::out_of_range(MESSAGE_DATA_IS_EMPTY);
		return iterator(this, Storage_::size_);
	}

	reverse_iterator rbegin() {
		return reverse_iterator(end());
	}

	reverse_iterator rend() {
		return reverse_iterator(begin());
	}

	const_iterator cbegin() {
		return const_iterator(begin());
	}

	const_iterator cend() {
		return const_iterator(end());
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