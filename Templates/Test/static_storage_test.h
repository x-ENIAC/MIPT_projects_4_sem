#ifndef STATIC_STORAGE_TEST_H
#define STATIC_STORAGE_TEST_H

#include "test_helpers.h"

#define PRINT_STATIC_ARRAY_INFO									\
	printf("\n> ARRAY INFO: size %ld\n", array.size());

namespace Static_storage_test {

void test_simply_int_array() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	try {
		Array<int, Static_storage<5>::type> array;
		size_t arr_size = array.size();

		for(size_t i = 0; i < arr_size; ++i)
			array[i] = rand() % 100 + 1;

		PRINT_STATIC_ARRAY_INFO
		PRINT_INT_ARRAY
	} catch (std::exception& exc) {
		printf("\nEXCEPTION: %s\n", exc.what());
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_bool_array() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	try {
		Array<bool, Dynamic_storage> array(6, true);

		PRINT_INT_ARRAY
		PRINT_DYNAMIC_ARRAY_INFO

	} catch (std::exception& exc) {
		printf("\nEXCEPTION: %s\n", exc.what());
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_resize() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	try {
		Array<int, Static_storage<16>::type> array;
		size_t arr_size = array.size();		

		for(int i = 0; i < arr_size; ++i)
			array[i] = i;

		PRINT_STATIC_ARRAY_INFO
		PRINT_INT_ARRAY

		array.resize(5);

		PRINT_STATIC_ARRAY_INFO
		PRINT_INT_ARRAY

		array.clear();
	} catch (std::exception& exc) {
		printf("\nEXCEPTION: %s\n", exc.what());
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

}

#endif