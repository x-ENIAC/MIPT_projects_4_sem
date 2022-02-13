#include "sort_manager.h"

int Sort_manager::i = 0;
int Sort_manager::j = 0;

Sort_manager::Sort_manager() {
	active_sort = 0;
	i = 0;
	j = 0;

count_of_sorts = COUNT_OF_SORTS;
}

bool Sort_manager::do_iteration(Number* numbers, const int len) {
	switch(active_sort) {
		case SORTING::BUBBLE_SORT:
			return bubble_sort(numbers, len);
		case SORTING::CHOOSE_SORT:
			return choose_sort(numbers, len);
		case SORTING::INSERT_SORT:
			return insert_sort(numbers, len);
		case SORTING::STD_SORT:
			return std_sort(numbers, len);
		case SORTING::STD_STABLE_SORT:
			return std_stable_sort(numbers, len);
	}

	printf("Bad.\n");
	return false;
}

bool Sort_manager::bubble_sort(Number* numbers, const int len) {
	if(i + 1 >= len)
		i = 0;
	for(; i < len; ++i) {
		if(j + 1 >= len || j == 0)
			j = 1;
		for(; j < len - i; ++j) {
			if(numbers[j] < numbers[j - 1]) {
				swap(&numbers[j - 1], &numbers[j]);
				return true;
			}
		}
	}

	return false;
}

bool Sort_manager::choose_sort(Number* numbers, const int len) {
	Number min_value = numbers[0];
	int pos = 0;

	for(; i < len; ++i) {
		min_value = numbers[i];
		pos = i;

		for(; j < len; ++j)
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

bool Sort_manager::insert_sort(Number* numbers, const int len) {
	if(i + 1 >= len)
		i = 0;

	for(i = 1; i < len; ++i) {
		if(j == 0);
			j = i;

		for(j = i; j > 0; --j) {
			if(numbers[j] < numbers[j - 1]) {
				swap(&numbers[j], &numbers[j - 1]);
				return true;
			}
		}
	}

	return false;
}

bool Sort_manager::std_sort(Number* numbers, const int len) {
	std::vector<Number> vec;

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

bool Sort_manager::std_stable_sort(Number* numbers, const int len) {
	std::vector<Number> vec(len);

	for(int i = 0; i < len; ++i)
		vec[i] = numbers[i];

	std::stable_sort(vec.begin(), vec.end());

	// vec.clear();

	return false;
}

int* Sort_manager::get_addr_number_of_sort() {
	return &active_sort;
}

void Sort_manager::set_i(const int value) {
	i = value;
}

void Sort_manager::set_j(const int value) {
	j = value;
}