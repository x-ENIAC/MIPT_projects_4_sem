#ifndef STRING_TEST_H
#define STRING_TEST_H

#include <cstdio>
#include <cstring>
#include "../String/string.h"

const size_t STANDART_TESTING_LINE_LEN = 24;

#define PRINT_STRING(str)				\
	size_t length = str.size();			\
	for(size_t i = 0; i < length; ++i)	\
		printf("%c", str[i]);			\
	printf("\n");

#define START_TEST_FUNC(FUNC)									\
	printf("\n\n\n\n");											\
	size_t line_len = STANDART_TESTING_LINE_LEN + strlen(FUNC);	\
	for(size_t i = 0; i < line_len; ++i)						\
		printf("-");											\
	printf("\n-------- START %s --------\n", FUNC);

#define END_TEST_FUNC(FUNC)										\
	printf("\n--------- END %s ---------\n", FUNC);				\
	for(size_t i = 0; i < line_len; ++i)						\
		printf("-");											\
	printf("\n");

namespace String_test {

void test_constructor_string() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> str(12, 's');
	PRINT_STRING(str)

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

}

#endif