#include <cstdio>
#include <cmath>
#include <vector>
#include "controller.h"

Controller_data_charts::Controller_data_charts(const int arg_start_len, const int arg_step, const int arg_count_of_operations) :
	start_len(arg_start_len), step(arg_step), count_of_operations(arg_count_of_operations) {

	printf("[Controller] init, start_len %d, step %d, count_of_operations %d\n", start_len, step, count_of_operations);

	// data = new Number*[count_of_operations];
	// std::vector<Number*> 

	data.resize(count_of_operations);

	int now_len = start_len;
	for(int i = 0; i < count_of_operations; ++i) {
		data[i] = new Number[now_len];
		now_len += step;
	}

	refresh_data();
}

Controller_data_charts::~Controller_data_charts() {
	for(int i = 0; i < count_of_operations; ++i)
		delete[] data[i];
	// delete[] data;
}

void Controller_data_charts::refresh_data() {
	int now_len = start_len;

	for(int i = 0; i < count_of_operations; ++i) {
		for(int j = 0; j < now_len; ++j) {
			data[i][j].value = rand() % 1000;
			data[i][j].set_pos(j);
		}

		now_len += step;
	}
}

void Controller_data_charts::start_research(std::vector<Number> &numbers, const int len, const int index, graph_pair* pair) {
	printf("start start_research index %d!\n", index);

	printf("[start_research] start\n");
	Number* copy_data = new Number[len];

	for(int i = 0; i < len; ++i)
		copy_data[i] = numbers[i];

	standartized_sorts[index](copy_data, len, pair);
	printf("[start_research] end\n");
	delete[] copy_data;
	return;


	int now_len = start_len;
	// Number** copy_data = new Number*[count_of_operations];

	// for(int i = 0; i < count_of_operations; ++i) {
	// 	copy_data[i] = new Number[now_len];

	// 	for(int j = 0; j < now_len; ++j)
	// 		copy_data[i][j] = data[i][j];

	// 	now_len += step;
	// }

	// std::vector<Number*> copy_data(count_of_operations, nullptr);
	// for(int i = 0; i < count_of_operations; ++i) {
	// 	copy_data[i] = new Number[now_len];

	// 	for(int j = 0; j < now_len; ++j)
	// 		copy_data[i][j] = data[i][j];

	// 	now_len += step;
	// }

	// comparisons = 0;
	// assignments = 0;

	// now_len = start_len;
	// for(int i = 0; i < count_of_operations; ++i) {
	// 	printf("before sort\n");
	// 	standartized_sorts[index](copy_data[i], now_len);
	// 	printf("I am here!\n");
	// 	// printf("%d %d %d %d\n", pairs[i].sorting, pairs[i].assign, pairs[i].compare, pairs[i].len_array);
	// 	// App::get_app()->get_view_manager()->update_charts(pair);
	// 	now_len += step;
	// 	// printf("\n\n");
	// }

	// for(int i = 0; i < count_of_operations; ++i)
	// 	delete[] copy_data[i];
	// delete[] copy_data;
}

int Controller_data_charts::get_count_of_operations() {
	return count_of_operations;
}