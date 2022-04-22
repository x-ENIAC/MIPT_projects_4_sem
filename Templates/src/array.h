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

const size_t SIZEOF_UCHAR = sizeof(unsigned char);
template <
	template <typename storage_type> typename Storage
	>
class Array<bool, Storage>: public Storage<unsigned char> {
  private:
	struct Bool_proxy {
		Array<bool, Storage>* array_;
		size_t index_;
		bool value_;
		unsigned char bit_;

		Bool_proxy(Array<bool, Storage>* array) : array_(array) {
			update(0);
		}

		void update(const size_t ind) {
			index_ = ind / SIZEOF_UCHAR;
			bit_ = ind % SIZEOF_UCHAR;
			value_ = (array_->get_value(index_) << bit_) & 1;
		}

		operator bool() const {
			return value_;
		}

		void set_value(const bool& new_value) {
			value_ = new_value;
			array_->set_value(index_, (unsigned char)(array_->get_value(index_) & ~(1 << bit_)));
			array_->set_value(index_, (unsigned char)(array_->get_value(index_) | (value_ << bit_)));
		}
	};

	Bool_proxy bool_proxy;
	size_t bools_count;
  public:
	typedef Storage<unsigned char> BStorage_;

	Array(): BStorage_(), bool_proxy(this), bools_count(0) {}
	Array(size_t size, const bool& init_element):
		BStorage_((size / SIZEOF_UCHAR + ((size % SIZEOF_UCHAR) != 0)), init_element), bool_proxy(this) {
		bools_count = (size / SIZEOF_UCHAR + ((size % SIZEOF_UCHAR) != 0));
	}

	Array(std::initializer_list<bool> list) :
		BStorage_(list.size() / SIZEOF_UCHAR + ((list.size() % SIZEOF_UCHAR) != 0), 0),
		bool_proxy(this), bools_count(list.size()) {

		size_t i = 0;
		for(auto element = list.begin(); element != list.end(); ++element) {
			BStorage_::data(i) = *element;
			++i;
		}
	}

	bool operator[](size_t index) {
		bool_proxy.update(index);
		return bool_proxy;
	}

	unsigned char get_value(const size_t index) {
		return BStorage_::data(index);
	}

	void set_value(const size_t index, const unsigned char value) {
		BStorage_::data(index) = value;
	}	

	bool& front() {
		bool_proxy.update(0);
		return bool_proxy;
	}

	bool& back() {
		bool_proxy.update(bools_count - 1);
		return bool_proxy;
	}

	void resize(size_t new_size) {
		BStorage_::resize(new_size / SIZEOF_UCHAR + ((new_size % SIZEOF_UCHAR) != 0));
	}

	void resize(size_t new_size, const bool& init_value) {
		unsigned char value = (init_value ? ((unsigned char)(-1)) : 0);
		BStorage_::resize(new_size / SIZEOF_UCHAR + ((new_size % SIZEOF_UCHAR) != 0), value);
	}

	void push_back(const bool& value) {
		if(bools_count % SIZEOF_UCHAR == SIZEOF_UCHAR - 1)
			BStorage_::push_back(0);

		bool_proxy.update(bools_count);
		++bools_count;
		bool_proxy.set_value(value);
	}

	void push_back(bool&& value) {
		if(bools_count % SIZEOF_UCHAR == SIZEOF_UCHAR - 1)
			BStorage_::push_back((unsigned char)0);

		bool_proxy.update(bools_count);
		++bools_count;
		bool_proxy.set_value(value);
	}	
};

#endif