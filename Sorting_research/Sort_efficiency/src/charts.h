#include "Editor/canvas.h"
#include "Editor/pencil.h"
#include "sorts.h"
#include "chart.h"
#include "Utils/my_vector.h"
#include "cmath"

#ifndef CHARTS_H
#define CHARTS_H

class Charts;
#include "app.h"

class Charts : public View_object {
	public:
	Chart** charts;
	int count_of_sorting;
	bool* is_visible;
	Colour* colours;

	Charts(const Point center, const double width, const double height, Pencil* pencil, const int arg_count_of_sorting) :
		View_object(center, width, height, LIGHT_GREY, Widget_types::CHART) {
			
		count_of_sorting = arg_count_of_sorting;
		// printf("%d...\n", count_of_sorting);

		is_visible = new bool[count_of_sorting + 1];
		for(int i = 0; i <= count_of_sorting; ++i)
			is_visible[i] = false;

		colours = new Colour[count_of_sorting + 1];
		colours[0] = BLACK;
		colours[1] = RED;
		colours[2] = GREEN;
		colours[3] = BLUE;
		colours[4] = PURPLE;

		charts = new Chart*[2];

		charts[0] = new Chart(Point(200, 200), 350, 350, pencil, "Comparison", arg_count_of_sorting, is_visible, colours, App::get_app()->get_controller()->get_count_of_operations());
		charts[1] = new Chart(Point(590, 200), 350, 350, pencil, "Assignment", arg_count_of_sorting, is_visible, colours, App::get_app()->get_controller()->get_count_of_operations());
	}

	~Charts() {
		delete[] is_visible;

		delete[] charts[0];
		delete[] charts[1];

		delete[] charts;
	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			// printf("begin draw chartsssssssssssss\n");
			charts[0]->draw(render, texture, screen);
			charts[1]->draw(render, texture, screen);
		}
		// printf("end draw chart\n\n");
	}

	void update_point(graph_pair &pair) {
		charts[0]->update_point(pair.sorting, pair.len_array, pair.compare);
		// printf("begin update assignment_chart\n");
		charts[1]->update_point(pair.sorting, pair.len_array, pair.assign);
	}
};

#endif