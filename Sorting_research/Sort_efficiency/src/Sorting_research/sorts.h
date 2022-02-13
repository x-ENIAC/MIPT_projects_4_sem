
#ifndef SORTS_H
#define SORTS_H

#include "number.h"

enum SORTING {
	BUBBLE_SORT 	= 0,
	CHOOSE_SORT 	= 1,
	INSERT_SORT 	= 2,
	STD_SORT 		= 3,
	STD_STABLE_SORT = 4
};

const int COUNT_OF_SORTS = 5;

static const char* text_sorts[] = {
	"Bubble sort",
	"Choose sort",
	"Insert sort",
	"Std sort",
	"Std stable sort"
};

struct graph_pair {
	SORTING sorting;
	int assign, compare, len_array;

	graph_pair() {
		sorting = BUBBLE_SORT;
		assign = compare = len_array = 0;
	}

	graph_pair(SORTING arg_sorting, const int arg_assign, const int arg_compare, const int arg_len_array) {
		sorting = arg_sorting;
		assign = arg_assign;
		compare = arg_compare;
		len_array = arg_len_array;
	}

	graph_pair& operator=(const graph_pair& right) {
		if(this != &right) {
			sorting = right.sorting;
			assign = right.assign;
			compare = right.compare;
			len_array = right.len_array;
		}

		return *this;
	}
};

typedef void (*standartized_sort)(Number*, int, graph_pair*);
extern standartized_sort standartized_sorts[];

const int MAX_LEN = 500;

inline void swap(const Number first, const Number second);

int cmp(const void* first_, const void* second_);

void bubble_sort(Number* numbers, const int len, graph_pair* pair);

void choose_sort(Number* numbers, const int len, graph_pair* pair);

void insert_sort(Number* numbers, const int len, graph_pair* pair);

void std_sort(Number* numbers, const int len, graph_pair* pair);

void std_stable_sort(Number* numbers, const int len, graph_pair* pair);

#endif