#ifndef STRING_H
#define STRING_H

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
	String() : String_storage_() {}
	String(size_t size, const char& init_element) : String_storage_(size, init_element) {}
	String(std::initializer_list<CharT> list): String_storage_(list) {}

	CharT& operator[](size_t index) {
		if(index > String_storage_::size_)
			throw std::out_of_range(MESSAGE_BAD_INDEX);
		return String_storage_::at(index);
	}
};

#endif