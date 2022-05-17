#include "Test/string_test.h"

void string_tests() {
	String_test::test_constructor_string();
	String_test::test_sso();
	String_test::test_push_pop_back();
	String_test::test_append();
	String_test::test_comparisons();
	String_test::test_std_find();
	String_test::test_std_sort();
	String_test::test_range_based_for();
}

int main() {
	string_tests();
}