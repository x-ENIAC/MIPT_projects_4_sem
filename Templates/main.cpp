#include <iostream>
#include <string>
#include "src/array.h"

#include "Test/dynamic_storage_test.h"
#include "Test/static_storage_test.h"
// #include "Test/chunked_storage_test.h"

void dynamic_tests() {
	// Dynamic_storage_test::test_resize();
	// Dynamic_storage_test::test_simply_int_array();
	Dynamic_storage_test::test_iterator();
	Dynamic_storage_test::test_iterator_find();
}

void static_tests() {
	Static_storage_test::test_resize();
	Static_storage_test::test_simply_int_array();
}


void chunked_tests() {
	// Chunked_storage_test::test_resize();
	// Chunked_storage_test::test_simply_int_array();
}

int main(int argc, char const* argv[]) {

	dynamic_tests();
	// static_tests();

	return 0;
}