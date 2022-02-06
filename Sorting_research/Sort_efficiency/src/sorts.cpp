#include <stdio.h>
#include <vector>
#include <algorithm>
#include "sorts.h"
// #include "number.h"


int comparisons = 0;
int assignments = 0;

standartized_sort standartized_sorts[] = {
	bubble_sort,
	choose_sort,
	insert_sort,
	std_sort,
	std_stable_sort
};

inline void swap(Number* first, Number* second) {
	Number tmp = *first;
	*first = *second;
	*second = tmp;
}

inline void swap(Number first, Number second) {
	Number tmp = first;
	first = second;
	second = tmp;
}

void bubble_sort(Number* numbers, const int len, graph_pair* pair) {
	// printf("begin bubble sort\n");
	for(int i = 0; i < len; ++i)
		for(int j = 1; j < len - i; ++j)
			if(numbers[j] < numbers[j - 1])
				swap(&numbers[j - 1], &numbers[j]);

	// printf("end bubble sort\n");
	// printf("len %d, assignments %d, comparisons %d\n", len, assignments, comparisons);
	*pair = graph_pair(SORTING::BUBBLE_SORT, assignments, comparisons, len);
	return;
}

void choose_sort(Number* numbers, const int len, graph_pair* pair) {
	Number min_value = numbers[0];
	int pos = 0;

	for(int i = 0; i < len; ++i) {
		min_value = numbers[i];
		pos = i;

		for(int j = i; j < len; ++j)
			if(numbers[j] < min_value) {
				min_value = numbers[j];
				pos = j;
			}

		swap(&numbers[pos], &numbers[i]);
	}

	*pair = {SORTING::CHOOSE_SORT, assignments, comparisons, len};
	return;
}

void insert_sort(Number* numbers, const int len, graph_pair* pair) {
	for(int i = 1; i < len; ++i)
		for(int j = i; j > 0; --j) {
			if(numbers[j] < numbers[j - 1])
				swap(&numbers[j], &numbers[j - 1]);
		}

	*pair = {SORTING::INSERT_SORT, assignments, comparisons, len};
	return;
}

void std_sort(Number* numbers, const int len, graph_pair* pair) {
	// std::vector<Number> vec(len, {0, 0});
	// printf("!!!!! len = %d\n", len);

	// for(int i = 0; i < len; ++i)
	// 	// vec[i] = numbers[i];
	// 	vec.push_back(numbers[i]);

	// std::sort(vec.begin(), vec.end());

	// // vec.clear();
	// printf("after clear..\n");

	*pair = {SORTING::STD_SORT, assignments, comparisons, len};
	return;
}

void std_stable_sort(Number* numbers, const int len, graph_pair* pair) {
	std::vector<Number> vec(len);

	for(int i = 0; i < len; ++i)
		vec[i] = numbers[i];

	std::stable_sort(vec.begin(), vec.end());

	// vec.clear();

	*pair = {SORTING::STD_STABLE_SORT, assignments, comparisons, len};
	return;
}