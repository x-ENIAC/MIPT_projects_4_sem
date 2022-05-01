#ifndef STRING_STORAGE_H
#define STRING_STORAGE_H

#include "allocator.h"

const size_t SMALL_SIZE = 8;

template < typename CharT >
class String_storage {
  protected:
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

  public:
	String_storage() : data_{}, size_(0) {}
	String_storage(const CharT* string, size_t count) : size_(size) {
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

	// String_storage(const String_storage& other, size_t pos = 0, size_t count = other.size()) : size_(count) {
	// 	if(other.is_size_small())
	// 		construct_static(other.small_data_ + pos);
	// 	else
	// 		construct_dynamic(other.data_.data_ + pos);
	// }

	~String_storage() {
		if(!is_size_small()) {
			allocator_.deallocate(data_.data_);
			data_.capacity_ = 0;
		}

		size_ = 0;
	}

	inline bool is_size_small() const {
		return size_ <= SMALL_SIZE;
	}

	CharT& at(size_t index) {
		if(is_size_small())
			return small_data_[index];
		return data_.data_[index];
	}

	size_t size() const {
		return size_;
	}

	bool empty() const {
		return (size_ == 0);
	}

  private:

	void construct_dynamic(const CharT* string) {
		size_t new_capacity = size_ * 2;
		CharT* new_data = allocator_.allocate(new_capacity);

		for(size_t i = 0; i < size_; ++i)
			new_data[i] = string[i];

		data_.data_ = new_data;
		data_.capacity_ = new_capacity;
	}

	void construct_dynamic(const CharT& value) {
		size_t new_capacity = size_ * 2;
		CharT* new_data = allocator_.allocate(new_capacity);

		for(size_t i = 0; i < size_; ++i)
			new_data[i] = value;

		data_.data_ = new_data;
		data_.capacity_ = new_capacity;
	}

	void construct_static(const CharT* string) {
		for(size_t i = 0; i < size_; ++i)
			small_data_[i] = string[i];
	}

	void construct_static(const CharT& value) {
		for(size_t i = 0; i < size_; ++i)
			small_data_[i] = value;
	}	
};

#endif