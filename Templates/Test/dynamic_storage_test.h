#include <algorithm>
#include <string.h>

#ifndef DYNAMIC_STORAGE_TEST_H
#define DYNAMIC_STORAGE_TEST_H

#include "test_helpers.h"

#define PRINT_DYNAMIC_ARRAY_INFO															\
	printf("> ARRAY INFO: size %ld, capacity %ld\n", array.size(), array.capacity());


namespace Dynamic_storage_test {

void test_simply_int_array() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	try {
		Array<int, Dynamic_storage> array(5, 1);

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
		Array<int, Dynamic_storage> array(16, 0);

		for(int i = 0; i < 16; ++i) {
			array[i] = i + 1;
		}

		PRINT_DYNAMIC_ARRAY_INFO
		PRINT_INT_ARRAY

		array.resize(5);

		PRINT_DYNAMIC_ARRAY_INFO
		PRINT_INT_ARRAY

		array.clear();
	} catch (std::exception& exc) {
		printf("\nEXCEPTION: %s\n", exc.what());
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_iterator() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	try {
		Array<int, Dynamic_storage> array(16, 0);

		for(int i = 0; i < 16; ++i)
			array[i] = i + 1;

		PRINT_DYNAMIC_ARRAY_INFO
		PRINT_INT_ARRAY

		printf("\n> Print with iterator:");
		for(auto it = array.begin(); it != array.end(); ++it)
			printf(" %d", *it);
		printf("\n");


		printf("\n\n> Print with iterator (reverse):");
		for(auto it = array.rbegin(); it != array.rend(); ++it)
			printf(" %d", *it);
	} catch (std::exception& exc) {
		printf("\nEXCEPTION: %s\n", exc.what());
	}		

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_iterator_find() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	try {
		Array<int, Dynamic_storage> array = {1, 2, 3, 4, 5, 6, 7, 8};

		PRINT_DYNAMIC_ARRAY_INFO
		PRINT_INT_ARRAY

		auto it = std::find(array.begin(), array.end(), 13);
		if(it != array.end())
			printf("Element exists in array\n");
		else
			printf("Element doesn't exist in array\n");
	} catch (std::exception& exc) {
		printf("\nEXCEPTION: %s\n", exc.what());
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_iterator_copy() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	try {
		Array<int, Dynamic_storage> array = {1, 2, 3, 4, 5, 6, 7, 8};

		PRINT_DYNAMIC_ARRAY_INFO
		PRINT_INT_ARRAY

		Array<int, Dynamic_storage> array_copy(array.size(), 0);

	    std::copy(array.begin(), array.end(), array_copy.begin());

		for(auto i = array_copy.begin(); i != array_copy.end(); ++i)
			printf("%d ", *i);

	} catch (std::exception& exc) {
		printf("\nEXCEPTION: %s\n", exc.what());
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

}

#endif