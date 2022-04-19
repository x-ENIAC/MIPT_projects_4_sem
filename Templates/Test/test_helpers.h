#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#define PRINT_INT_ARRAY	{				\
	size_t arr_size = array.size();		\
	printf("> ");						\
	for(int i = 0; i < arr_size; ++i)	\
		printf("%d ", array[i]);		\
	printf("\n");						\
}

const size_t STANDART_TESTING_LINE_LEN = 24;

#define START_TEST_FUNC(FUNC)									\
	printf("\n\n\n\n");											\
	size_t line_len = STANDART_TESTING_LINE_LEN + strlen(FUNC);	\
	for(size_t i = 0; i < line_len; ++i)						\
		printf("-");											\
	printf("\n-------- START %s --------\n", FUNC);

#define END_TEST_FUNC(FUNC)										\
	printf("\n--------- END %s ---------\n", FUNC);				\
	for(size_t i = 0; i < line_len; ++i)						\
		printf("-");											\
	printf("\n");

#endif