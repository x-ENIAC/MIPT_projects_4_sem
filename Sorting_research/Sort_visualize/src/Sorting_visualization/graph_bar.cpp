#include "graph_bar.h"
#include "../app.h"
#include "../Math_structures/sort_manager.h"

Graph_bar::Graph_bar(const Point par_point, const double par_width, const double par_height, const Colour par_color, 
			Number_container* arg_number_container) :
View_object(par_point, par_width, par_height, par_color) {

	number_container = arg_number_container;
	heights = new int[number_container->get_count() + 1];
	colours = new Colour[number_container->get_count() + 1];
	fill_heights();

	number_of_sort = App::get_app()->get_sort_manager()->get_addr_number_of_sort();
}

void Graph_bar::fill_heights() {
	int count_numbers = number_container->get_count();
	double basis = 1.0 * rect->get_height() / number_container->get_max_value();

	for(int i = 0; i < count_numbers; ++i) {
		heights[i] = basis * number_container->numbers[i].value;
		colours[i] = BLUE;
	}
}

void Graph_bar::update() {
	int count = number_container->get_count();

	int is_something_change = App::get_app()->get_sort_manager()->do_iteration(number_container->get_numbers(), count);

	std::vector<int> changed_pos;

	for(int i = 0; i < count; ++i) {
		if(i != number_container->numbers[i].pos) {
			changed_pos.push_back(i);
		}
	}

	if(changed_pos.size() == 2)
		std::swap(heights[changed_pos[0]], heights[changed_pos[1]]);

	for(int i = 0; i < count; ++i) {
		if(i != number_container->numbers[i].pos)
			number_container->numbers[i].pos = i;
	}
}