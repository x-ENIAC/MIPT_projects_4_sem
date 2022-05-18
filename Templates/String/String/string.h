#ifndef STRING_H
#define STRING_H

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>

#include "error_codes.h"
#include "string_storage.h"

template <typename CharT>
class String : public String_storage<CharT> {
  private:
	typedef String_storage<CharT> String_storage_;

  public:
	String() 
	: String_storage_() {}

	String(const CharT* string, size_t count)
	: String_storage_(string, count) {}

	String(const CharT* string)
	: String_storage_(string, strlen(string)) {}

	String(const String& other)
	: String_storage_(other) {}

	String(const String& other, size_t pos)
	: String_storage_(other, pos) {}

	String(const String& other, size_t pos, size_t count)
	: String_storage_(other, pos, count) {}

	String(String&& other)
	: String_storage_(other) {}

	String(size_t size, const char& init_element)
	: String_storage_(size, init_element) {}

	String(String_storage_&& other)
	: String_storage_(std::move(other)) {}

	static String view(CharT** buffer, size_t count) {
		return String(String_storage_::view(buffer, count));
	}

	const String& operator=(const String& other) {
		String_storage_::operator=(other);
		return *this;
	}

	const String& operator=(const String&& other) {
		String_storage_::operator=(other);
		return *this;
	}

	CharT& operator[](size_t index) {
		return String_storage_::at(index);
	}

	const CharT& front() {
		if(size() == 0)
			throw std::out_of_range(MESSAGE_DATA_IS_EMPTY);
		return (*this)[0];
	}

	const CharT& back() {
		if(size() == 0)
			throw std::out_of_range(MESSAGE_DATA_IS_EMPTY);
		return (*this)[size() - 1];
	}

	void push_back(CharT value) {
		String_storage_::push_back(value);
	}

	void pop_back() {
		if(size() == 0)
			throw std::out_of_range(MESSAGE_DATA_IS_EMPTY);
		String_storage_::pop_back();		
	}

	String& operator+=(const String& string) {
		return append(string);
	}

	String& operator+=(CharT value) {
		return append(value, 1);
	}

	String operator+(const String& other) {
		String res = *this;
		res += other;
		return res;
	}

	String& append(const CharT* string, size_t count) {
		String_storage_::redistribute_memory(size() + count);

		for(size_t i = 0; i < count; ++i)
			String_storage_::push_back(string[i]);

		return *this;
	}

	String& append(const String& string) {
		return append(string.c_str(), string.size());
	}

	String& append(CharT& value, size_t count) {
		String_storage_::redistribute_memory(size() + count);

		for(size_t i = 0; i < count; ++i)
			String_storage_::push_back(value);

		return *this;
	}

	size_t size() const {
		return String_storage_::size();
	}

	size_t capacity() const {
		return String_storage_::capacity();
	}

	CharT* data() {
		return String_storage_::data();
	}

	const CharT* data() const {
		return String_storage_::data();
	}

	// --------- comparison operators -----------------

	bool operator==(const String& other) const {
		size_t other_size = other.size();

		if(size() != other_size)
			return false;

		for(size_t i = 0; i < other_size; ++i)
			if(String_storage_::at(i) != other.at(i))
				return false;
		return true;
	}

	bool operator!=(const String& other) const {
		size_t other_size = other.size();

		if(size() != other_size)
			return false;

		bool flag = true;

		for(size_t i = 0; i < other_size; ++i)
			if(String_storage_::at(i) != other.at(i))
				flag = false;
		return flag;
	}

	bool operator<(const String& other) const {
		size_t other_size = other.size();

		if(size() != other_size)
			return (size() < other_size);

		for(size_t i = 0; i + 2 < other_size; ++i)		// because '\0'
			if(String_storage_::at(i) > other.at(i))
				return false;

		if(String_storage_::at(other_size - 2) >= other.at(other_size - 2))
			return false;
		return true;
	}

	bool operator<=(const String& other) const {
		size_t other_size = other.size();

		if(size() != other_size)
			return (size() < other_size);

		for(size_t i = 0; i + 2 < other_size; ++i)		// because '\0'
			if(String_storage_::at(i) > other.at(i))
				return false;

		if(String_storage_::at(other_size - 2) > other.at(other_size - 2))
			return false;
		return true;
	}

	bool operator>(const String& other) const {
		size_t other_size = other.size();

		if(size() != other_size)
			return (size() > other_size);

		for(size_t i = 0; i + 2 < other_size; ++i)		// because '\0'
			if(String_storage_::at(i) < other.at(i))
				return false;

		if(String_storage_::at(other_size - 2) <= other.at(other_size - 2))
			return false;
		return true;
	}

	bool operator>=(const String& other) const {
		size_t other_size = other.size();

		if(size() != other_size)
			return (size() > other_size);

		for(size_t i = 0; i + 2 < other_size; ++i)		// because '\0'
			if(String_storage_::at(i) < other.at(i))
				return false;

		if(String_storage_::at(other_size - 2) < other.at(other_size - 2))
			return false;
		return true;
	}

	// ----------------- iterator -----------------

	CharT* begin() {
		return data();
	}

	CharT* end() {
		return data() + size();
	}
};

#endif