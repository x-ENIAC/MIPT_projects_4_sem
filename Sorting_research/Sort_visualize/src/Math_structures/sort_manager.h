#ifndef SORT_MANAGER_H
#define SORT_MANAGER_H

#include <algorithm>
#include <cstdio>
#include <vector>
#include "sorts.h"

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


class Sort_manager {
  public:

  	int active_sort;
  	static int i;
  	static int j;
  	int count_of_sorts;

  	Sort_manager();

  	bool do_iteration(Number* numbers, const int len);

	bool bubble_sort(Number* numbers, const int len);

	bool choose_sort(Number* numbers, const int len);

	bool insert_sort(Number* numbers, const int len);

	bool std_sort(Number* numbers, const int len);

	bool std_stable_sort(Number* numbers, const int len);

	int* get_addr_number_of_sort();

	void set_i(const int value);

	void set_j(const int value);
};

#endif