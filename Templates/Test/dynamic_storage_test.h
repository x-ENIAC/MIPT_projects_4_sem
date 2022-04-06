#ifndef DYNAMIC_STORAGE_TEST_H
#define DYNAMIC_STORAGE_TEST_H

#define PRINT_INT_DYNAMIC_ARRAY	{		\
	size_t arr_size = array.size();		\
	printf("> ");						\
	for(int i = 0; i < arr_size; ++i)	\
		printf("%d ", array[i]);		\
	printf("\n");						\
}

#define PRINT_DYNAMIC_ARRAY_INFO															\
	printf("> ARRAY INFO: size %ld, capacity %ld\n", array.size(), array.capacity());


#define START_TEST_FUNC(FUNC) printf("\n\n---------------- START %s\n", FUNC);
#define END_TEST_FUNC(FUNC) printf("------------------ END %s\n", FUNC);

namespace Dynamic_storage_test {

void test_simply_int_array() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	try {
		Array<int, 5, Dynamic_storage> array(1);

		PRINT_INT_DYNAMIC_ARRAY
		PRINT_DYNAMIC_ARRAY_INFO
	} catch (std::exception& exc) {
		printf("\nEXCEPTION: %s\n", exc.what());
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_resize() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	try {
		Array<int, 16, Dynamic_storage> array;

		for(int i = 0; i < 20; ++i) {
			array.push_back(i + 1);
		}

		PRINT_INT_DYNAMIC_ARRAY
		PRINT_DYNAMIC_ARRAY_INFO

		array.resize(5);

		PRINT_INT_DYNAMIC_ARRAY
		PRINT_DYNAMIC_ARRAY_INFO

		array.clear();
	} catch (std::exception& exc) {
		printf("\nEXCEPTION: %s\n", exc.what());
	}

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_iterator() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	Array<int, 16, Dynamic_storage> array;

	for(int i = 0; i < 16; ++i)
		array.push_back(i + 1);

	PRINT_INT_DYNAMIC_ARRAY
	PRINT_DYNAMIC_ARRAY_INFO

	printf("\n> Print with iterator:");
	for(auto it = array.begin(); it != array.end(); ++it)
		printf(" %d", *it);
	printf("\n");

	printf("\n\n> Print with iterator (reverse):");
	for(auto it = array.rbegin(); it != array.rend(); ++it)
		printf(" %d", *it);
	printf("\n");	

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

void test_iterator_find() {
	START_TEST_FUNC(__PRETTY_FUNCTION__)

	Array<int, 8, Dynamic_storage> array = {1, 2, 3, 4, 5, 6, 7, 8};

	PRINT_INT_DYNAMIC_ARRAY
	PRINT_DYNAMIC_ARRAY_INFO

	// auto it = std::find(array.begin(), array.end(), 3);
	// if(it != array.end())
	// 	printf("Element 3 contains in array\n");
	// else
	// 	printf("Element 3 doesn't contain in array\n");

	END_TEST_FUNC(__PRETTY_FUNCTION__)
}

}

#endif