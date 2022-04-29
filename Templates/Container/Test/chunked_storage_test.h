#ifndef CHUNKED_STORAGE_TEST_H
#define CHUNKED_STORAGE_TEST_H

#include <algorithm>
#include "../src/chunked_mem.h"
#include "test_helpers.h"

#define PRINT_CHUNKED_ARRAY_INFO														\
	printf("> CHUNK ARRAY INFO: size %ld, capacity %ld, chunk_size %ld\n",				\
							array.size(), array.capacity(), array.chunk_size());

namespace Chunked_storage_test {

void test_simply_int_array() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	try {
		Array<int, Chunked_storage<4>::type> array{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

		PRINT_CHUNKED_ARRAY_INFO
		PRINT_INT_ARRAY
	} catch (std::exception& exc) {
		printf("\nEXCEPTION: %s\n", exc.what());
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_resize_push_pop_back() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	try {
		Array<int, Chunked_storage<5>::type> array(15, 666);

		PRINT_CHUNKED_ARRAY_INFO
		PRINT_INT_ARRAY
		printf("\n");

		array.resize(7);

		PRINT_CHUNKED_ARRAY_INFO
		PRINT_INT_ARRAY
		printf("\n");
		
		for(int i = 3; i < 10; ++i)
			array.push_back(i);

		PRINT_CHUNKED_ARRAY_INFO
		PRINT_INT_ARRAY
		printf("\n");

		for(int i = 0; i < 10; ++i)
			printf("\tpop_back res: %d\n", array.pop_back());

		printf("\n");
		PRINT_CHUNKED_ARRAY_INFO
		PRINT_INT_ARRAY
		printf("\n");

		array.clear();
	} catch (std::exception& exc) {
		printf("\nEXCEPTION: %s\n", exc.what());
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_iterator() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	try {
		Array<int, Chunked_storage<10>::type> array(15, 666);

		PRINT_CHUNKED_ARRAY_INFO
		PRINT_INT_ARRAY
		printf("\n");

		printf("\n> Print with iterator:");
		for(auto it = array.begin(); it != array.end(); ++it)
			printf(" %d", *it);
		printf("\n");


	} catch (std::exception& exc) {
		printf("\nEXCEPTION: %s\n", exc.what());
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

}

#endif