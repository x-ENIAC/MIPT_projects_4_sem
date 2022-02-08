#ifndef SORT_MANAGER_H
#define SORT_MANAGER_H

#include <algorithm>
#include <cstdio>
#include <vector>
#include "sorts.h"

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


class Sort_manager {
  public:

 //  	typedef bool (Sort_manager::standartized_sort)(Number*, int);
	// standartized_sort standartized_sorts[COUNT_OF_SORTS];

  	int active_sort;
  	static int i;
  	static int j;
  	int count_of_sorts;

  	// standartized_sort standartized_sorts[COUNT_OF_SORTS];

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