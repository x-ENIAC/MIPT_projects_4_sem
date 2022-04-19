#include <iostream>
#include <string>
#include "src/array.h"

#include "Test/dynamic_storage_test.h"
#include "Test/static_storage_test.h"
#include "Test/chunked_storage_test.h"

void dynamic_tests() {
	Dynamic_storage_test::test_simply_int_array();
	Dynamic_storage_test::test_resize();
	Dynamic_storage_test::test_iterator();
	Dynamic_storage_test::test_iterator_find();
	Dynamic_storage_test::test_iterator_copy();
}

void static_tests() {
	Static_storage_test::test_simply_int_array();
	Static_storage_test::test_resize();
}


void chunked_tests() {
	// Chunked_storage_test::test_simply_int_array();
	Chunked_storage_test::test_resize_push_pop_back();
	// Chunked_storage_test::test_iterator();
}

int main(int argc, char const* argv[]) {

	// dynamic_tests();
	// static_tests();
	chunked_tests();

	return 0;
}