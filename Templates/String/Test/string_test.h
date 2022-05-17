#ifndef STRING_TEST_H
#define STRING_TEST_H

#include <cstdio>
#include <cstring>
#include "../String/string.h"

const size_t STANDART_TESTING_LINE_LEN = 24;

#define PRINT_STRING_INFO(str) {													\
	size_t length = str.size();														\
	for(size_t i = 0; i < length; ++i)												\
		printf("%c", str[i]);														\
																					\
	if(str.is_static())																\
		printf(": sso, size %ld\n", length);										\
	else																			\
	if(str.is_dynamic())															\
		printf(": dynamic, size %ld, capacity %ld\n", length, str.capacity());		\
}

#define PRINT_STRING(str) {				\
	size_t length = str.size();			\
	for(size_t i = 0; i < length; ++i)	\
		printf("%c", str[i]);			\
	printf("\n");						\
}

#define PRINT_STRING_WITHOUT_NEW_LINE(str) {	\
	size_t length = str.size();					\
	for(size_t i = 0; i < length; ++i)			\
		printf("%c", str[i]);					\
}

#define START_TEST_FUNC(FUNC)									\
	printf("\n\n\n\n");											\
	size_t line_len = STANDART_TESTING_LINE_LEN + strlen(FUNC);	\
	for(size_t i = 0; i < line_len; ++i)						\
		printf("-");											\
	printf("\n-------- START %s --------\n\n", FUNC);

#define END_TEST_FUNC(FUNC)										\
	printf("\n--------- END %s ---------\n", FUNC);				\
	for(size_t i = 0; i < line_len; ++i)						\
		printf("-");											\
	printf("\n");

namespace String_test {

void test_constructor_string() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> str(12, 's');
	PRINT_STRING_INFO(str)

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_sso() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> str("sso", 4);
	PRINT_STRING_INFO(str)

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_push_pop_back() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> str("sso", 4);
	PRINT_STRING_INFO(str)

	for(char symbol = 'a'; symbol <= 'h'; ++symbol) {
		str.push_back(symbol);
		PRINT_STRING_INFO(str)
	}

	for(size_t i = 0; i < 9; ++i) {
		str.pop_back();
		PRINT_STRING_INFO(str);
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_append() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> str("sso", 4);

	// --------------------------------
	PRINT_STRING_WITHOUT_NEW_LINE(str)

	printf(" + ");

	for(char symbol = 'k'; symbol <= 't'; ++symbol) {
		str += symbol;
		printf("%c", symbol);
	}

	printf(" = ");
	PRINT_STRING(str)
	// --------------------------------

	char text[] = "allocator";

	PRINT_STRING_WITHOUT_NEW_LINE(str)
	printf(" + %s = ", text);

	str += text;
	PRINT_STRING(str)

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_comparisons() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> str1("sso", 4);
	String<char> str2("ssu", 4);
	String<char> str3("square", 7);

	// --------------------------------
	printf("%d - result of ", (str1 < str2));
	PRINT_STRING_WITHOUT_NEW_LINE(str1)
	printf(" < ");
	PRINT_STRING(str2);
	// --------------------------------
	printf("%d - result of ", (str3 < str2));
	PRINT_STRING_WITHOUT_NEW_LINE(str3)
	printf(" < ");
	PRINT_STRING(str2);
	// --------------------------------
	printf("%d - result of ", (str3 >= str2));
	PRINT_STRING_WITHOUT_NEW_LINE(str3)
	printf(" >= ");
	PRINT_STRING(str2);
	// --------------------------------
	printf("%d - result of ", (str1 <= str3));
	PRINT_STRING_WITHOUT_NEW_LINE(str1)
	printf(" <= ");
	PRINT_STRING(str3);
	// --------------------------------

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

template< typename CharT >
void helpful_for_test_std_find(String<CharT>& string, CharT symbol) {
	auto find_iter = std::find(string.begin(), string.end(), symbol);

	if(find_iter == string.end()) {
		PRINT_STRING_WITHOUT_NEW_LINE(string);
		printf(" contains %c\n", symbol);		
	} else {
		PRINT_STRING_WITHOUT_NEW_LINE(string)
		printf(" doesn't contain %c\n", symbol);
	}
}

void test_std_find() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> string("square", 7);

	helpful_for_test_std_find(string, 'p');
	helpful_for_test_std_find(string, 'q');	

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_std_sort() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> string("square", 7);

	PRINT_STRING_WITHOUT_NEW_LINE(string)

	printf(" -> ");
	std::sort(string.begin(), string.end());

	PRINT_STRING(string);

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_range_based_for() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> string("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");

	for(auto i : string)
		printf("%c", i);
	printf("\n");

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

}

#endif