#ifndef STRING_TEST_H
#define STRING_TEST_H

#include <cstdio>
#include <cstring>
#include "../String/string.h"

const size_t STANDART_TESTING_LINE_LEN = 24;

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

enum End_of_print_str {
	NOTHING,
	SPACE,
	END_LINE
};

template < typename CharT >
void print_string(String<CharT>& string, End_of_print_str is_need_new_line = END_LINE) {
	size_t len = string.size();
	for(size_t i = 0; i < len; ++i)
		printf("%c", string[i]);

	if(is_need_new_line == END_LINE)
		printf("\n");
	else
	if(is_need_new_line == SPACE)
		printf(" ");
}

template < typename CharT >
void print_string_info(String<CharT>& string) {
	size_t len = string.size();
	for(size_t i = 0; i < len; ++i)
		printf("%c", string[i]);

	if(string.is_static())
		printf(": sso, size %ld\n", len);
	else
	if(string.is_dynamic())
		printf(": dynamic, size %ld, capacity %ld\n", len, string.capacity());
	else
	 if(string.is_view())
	 	printf(": view, size %ld, capacity %ld\n", len, string.capacity());
}

void test_constructor_string() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> str(12, 's');
	print_string_info(str);

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_sso() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> str("sso", 4);
	print_string_info(str);

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_view() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	size_t buffer_size = 64;
	char* buffer = new char[buffer_size];
	memset(buffer, 0, buffer_size);
	strcpy(buffer, "Are you view?");

    String<char> string = String<char>::view(&buffer, buffer_size);

    print_string_info(string);

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_copy_on_write() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> string("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");

	for(auto i : string)
		printf("%c", i);
	printf("\n");

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_push_pop_back() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> str("sso", 4);
	print_string_info(str);

	for(char symbol = 'a'; symbol <= 'h'; ++symbol) {
		str.push_back(symbol);
		print_string_info(str);
	}

	for(size_t i = 0; i < 9; ++i) {
		str.pop_back();
		print_string_info(str);
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_append() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> str("sso", 4);

	// --------------------------------
	print_string(str, NOTHING);

	printf(" + ");

	for(char symbol = 'k'; symbol <= 't'; ++symbol) {
		str += symbol;
		printf("%c", symbol);
	}

	printf(" = ");
	print_string(str);
	// --------------------------------

	char text[] = "allocator";

	print_string(str, NOTHING);
	printf(" + %s = ", text);

	str += text;
	print_string(str);

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_assignment() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> dynamic1 = "dynamic...1";
	String<char> dynamic2 = "dynamic...2";
	String<char> sso1 = "sso1";
	String<char> sso2 = "sso2";

	printf("After assignment:\ndynamic1: ");
	print_string_info(dynamic1);
	
	printf("dynamic2: ");
	print_string_info(dynamic2);

	printf("sso1: ");
	print_string_info(sso1);

	printf("sso2: ");
	print_string_info(sso2);

	printf("\n");

	dynamic1 = sso2;
	sso1 = dynamic2;

	printf("\nBefore assignment:\ndynamic1: ");
	print_string_info(dynamic1);
	
	printf("dynamic2: ");
	print_string_info(dynamic2);

	printf("sso1: ");
	print_string_info(sso1);

	printf("sso2: ");
	print_string_info(sso2);

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}


void test_comparisons() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	String<char> str1("sso", 4);
	String<char> str2("ssu", 4);
	String<char> str3("square", 7);

	// --------------------------------
	printf("%d - result of ", (str1 < str2));
	print_string(str1, NOTHING);
	printf(" < ");
	print_string(str2);
	// --------------------------------
	printf("%d - result of ", (str3 < str2));
	print_string(str3, NOTHING);
	printf(" < ");
	print_string(str2);
	// --------------------------------
	printf("%d - result of ", (str3 >= str2));
	print_string(str3, NOTHING);
	printf(" >= ");
	print_string(str2);
	// --------------------------------
	printf("%d - result of ", (str1 <= str3));
	print_string(str1, NOTHING);
	printf(" <= ");
	print_string(str3);
	// --------------------------------

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

template< typename CharT >
void helpful_for_test_std_find(String<CharT>& string, CharT symbol) {
	auto find_iter = std::find(string.begin(), string.end(), symbol);

	if(find_iter == string.end()) {
		print_string(string, SPACE);
		printf("contains %c\n", symbol);		
	} else {
		print_string(string, SPACE);
		printf("doesn't contain %c\n", symbol);
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

	print_string(string, NOTHING);

	printf(" -> ");
	std::sort(string.begin(), string.end());

	print_string(string);

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