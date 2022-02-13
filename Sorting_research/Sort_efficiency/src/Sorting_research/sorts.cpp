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

int cmp(const void* first_, const void* second_) {
	Number first = *(Number*)first_;
	Number second = *(Number*)second_;

	if(first < second) {
		return -1;
	}
	else if(first > second) {
		--comparisons;
		return 1;
	}
	return 0;
}

void bubble_sort(Number* numbers, const int len, graph_pair* pair) {
	for(int i = 0; i < len; ++i)
		for(int j = 1; j < len - i; ++j)
			if(numbers[j] < numbers[j - 1])
				swap(&numbers[j - 1], &numbers[j]);

	if(pair)
		*pair = graph_pair(SORTING::BUBBLE_SORT, assignments, comparisons, len);
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

	if(pair)
		*pair = {SORTING::CHOOSE_SORT, assignments, comparisons, len};
}

void insert_sort(Number* numbers, const int len, graph_pair* pair) {
	for(int i = 1; i < len; ++i)
		for(int j = i; j > 0; --j) {
			if(numbers[j] < numbers[j - 1])
				swap(&numbers[j], &numbers[j - 1]);
		}

	if(pair)
		*pair = {SORTING::INSERT_SORT, assignments, comparisons, len};
}

void std_sort(Number* numbers, const int len, graph_pair* pair) {
	qsort(numbers, len, sizeof(numbers[0]), cmp);
	
	if(pair)
		*pair = {SORTING::STD_SORT, assignments, comparisons, len};
}

void std_stable_sort(Number* numbers, const int len, graph_pair* pair) {
	std::vector<Number> vec(len);

	for(int i = 0; i < len; ++i)
		vec[i] = numbers[i];

	std::stable_sort(vec.begin(), vec.end());

	if(pair)
		*pair = {SORTING::STD_STABLE_SORT, assignments, comparisons, len};
}