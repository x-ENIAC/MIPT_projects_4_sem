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
	// printf("\tSWAP (%d, %d) and (%d, %d)\n", first->value, first->pos, second->value, second->pos);
	Number tmp = *first;
	*first = *second;
	*second = tmp;
	// printf("\tRESULT SWAP (%d, %d) and (%d, %d)\n\n", first->value, first->pos, second->value, second->pos);
}

inline void swap(Number first, Number second) {
	Number tmp = first;
	first = second;
	second = tmp;
}

bool bubble_sort(Number* numbers, const int len) {
	// printf("begin bubble sort\n");
	for(int i = 0; i < len; ++i)
		for(int j = 1; j < len - i; ++j) {
			// printf("\tcheck %d and %d\n", numbers[j], numbers[j - 1]);
			if(numbers[j] < numbers[j - 1]) {
				swap(&numbers[j - 1], &numbers[j]);
				// printf("\tEEEE\n");
				return true;
			}
		}

	// printf("end bubble sort\n");
	// printf("len %d, assignments %d, comparisons %d\n", len, assignments, comparisons);
	return false;
}

bool choose_sort(Number* numbers, const int len) {
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

		if(pos != i) {
			swap(&numbers[pos], &numbers[i]);
			return true;
		}
	}

	return false;
}

bool insert_sort(Number* numbers, const int len) {
	for(int i = 1; i < len; ++i)
		for(int j = i; j > 0; --j) {
			if(numbers[j] < numbers[j - 1]) {
				swap(&numbers[j], &numbers[j - 1]);
				return true;
			}
		}

	return false;
}

bool std_sort(Number* numbers, const int len) {
	std::vector<Number> vec;
	printf("!!!!! len = %d\n", len);

	Number tmp = {}, tmp1 = {};
	for(int i = 0; i < len; ++i) {
		// tmp = numbers[i];

		// int v = tmp.value;
		// tmp1.value = v;;
		vec.push_back(numbers[i]);
		// vec.push_back(numbers[i]);
	}
	// 	vec.push_back(numbers[i]);

	for(int i = 0; i < vec.size(); ++i)
		printf("%d ", vec[i].value);
	printf("\n");

	printf("before sort\n");
	std::sort(vec.begin(), vec.begin() + 17);
	printf("after sort\n");

	// for(int i = 0; i < len; ++i)
	// 	vec.pop_back();

	vec.clear();
	printf("after clear..\n");

	return false;
}

bool std_stable_sort(Number* numbers, const int len) {
	std::vector<Number> vec(len);

	for(int i = 0; i < len; ++i)
		vec[i] = numbers[i];

	std::stable_sort(vec.begin(), vec.end());

	// vec.clear();

	return false;
}