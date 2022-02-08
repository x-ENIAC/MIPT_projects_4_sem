#include "../number.h"
#include "../sorts.h"
#include <vector>

#ifndef CONTROLLER_H
#define CONTROLLER_H
// class Controller_data_charts;
// #include "../app.h"

class Controller_data_charts {
  public:
	int start_len;
	int step;
	int count_of_operations;

	// Number** data;
	std::vector<Number*> data;

	Controller_data_charts(const int arg_start_len, const int arg_step, const int arg_count_of_operations);

	~Controller_data_charts();

	void refresh_data();

	// void start_research(const int index); // , graph_pair* pairs
	void start_research(std::vector<Number> &numbers, const int len, const int index, graph_pair* pair);

	int get_count_of_operations();

	int get_step() {
		return step;
	}

	int get_start_len() {
		return start_len;
	}

};

#endif