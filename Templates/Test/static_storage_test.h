#ifndef STATIC_STORAGE_TEST_H
#define STATIC_STORAGE_TEST_H

#define PRINT_INT_ARRAY	{				\
	size_t arr_size = array.size();		\
	printf("> ");						\
	for(int i = 0; i < arr_size; ++i)	\
		printf("%d ", array[i]);		\
	printf("\n");						\
}

#define PRINT_ARRAY_INFO									\
	printf("\n> ARRAY INFO: size %ld\n", array.size());

#define START_TEST_FUNC(FUNC) printf("\n\n---------------- START %s\n", FUNC);
#define END_TEST_FUNC(FUNC) printf("------------------ END %s\n", FUNC);

namespace Static_storage_test {

void test_simply_int_array() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	try {
		Array<int, 5, Static_storage> array;

		PRINT_ARRAY_INFO
		PRINT_INT_ARRAY
	} catch (std::exception& exc) {
		printf("\nEXCEPTION: %s\n", exc.what());
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_resize() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	try {
		const size_t size = 16;
		Array<int, size, Static_storage> array;

		for(int i = 0; i < size; ++i)
			array[i] = i;

		PRINT_ARRAY_INFO
		PRINT_INT_ARRAY

		array.resize(5);

		PRINT_ARRAY_INFO
		PRINT_INT_ARRAY

		array.clear();
	} catch (std::exception& exc) {
		printf("\nEXCEPTION: %s\n", exc.what());
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

}

#endif