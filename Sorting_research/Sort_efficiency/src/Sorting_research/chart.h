#include "../Editor/canvas.h"
#include "../Editor/pencil.h"
#include "sorts.h"
#include "../Utils/my_vector.h"
#include <cmath>

#ifndef CHART_H
#define CHART_H

struct my_pair {
	int x, y;

	my_pair() {
		x = y = 0;
	}
};

const int X_SCALE = 13; // 500
const int Y_SCALE = 3000; // 25000

class Chart : public View_object {
  public:
	Canvas* canvas;
	my_pair** coords;
	Text* text;

	int count_of_sorting;
	bool* is_visible;
	Colour* colours;
	int count_of_operations;

	Chart(const Point center, const double width, const double height, Pencil* pencil, const char* arg_text,
			const int arg_count_of_sorting, bool* arg_is_visible, Colour* arg_colours, const int arg_count_of_operations) :
	  View_object(center, width, height, LIGHT_GREY, Widget_types::CHART) {
		canvas = new Canvas(center, width, height, WHITE, pencil);

		count_of_sorting = arg_count_of_sorting;
		count_of_operations = arg_count_of_operations;
		coords = new my_pair*[count_of_sorting + 1];

		text = new Text(Point(center.x, height / 2 + 30 + center.y), arg_text, 200, 50, BLACK);

		for(int i = 0; i <= count_of_sorting; ++i)
			coords[i] = new my_pair[int(width) + 1];


		is_visible = arg_is_visible;
		colours = arg_colours;
	}

	~Chart() {
		delete canvas;

		for(int i = 0; i < count_of_sorting; ++i)
			delete[] coords[i];
		delete[] coords;
		delete[] is_visible;
	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			rect->draw(*render);

			canvas->draw(render, texture, screen);

			Point left_down_corner = rect->get_left_down_corner(), last_point = {};
			int width = rect->get_width(), height = rect->get_height();
			int iters = count_of_sorting;
			
			int x_scale = -10000, y_scale = -100000;

			for(int sort = 0; sort < count_of_sorting; ++sort) {
				if(!is_visible[sort])
					continue;

				for(int i = 0; i < iters; ++i) {
					if(coords[sort][i].x > x_scale)
						x_scale = coords[sort][i].x;
					if(coords[sort][i].y > y_scale)
						y_scale = coords[sort][i].y;
				}
			}

			for(int sort = 0; sort < count_of_sorting; ++sort) {
				if(!is_visible[sort])
					continue;

				for(int i = 0; i < iters; ++i) {
					Point now_point = {};
					now_point.x = left_down_corner.x + width / x_scale * coords[sort][i].x;

					if(coords[sort][i].y != 0)
						now_point.y = left_down_corner.y - height * (coords[sort][i].y) / y_scale;
					else
						now_point.y = left_down_corner.y;

					if(!rect->is_point_belongs_to_rectangle(now_point))
						continue;

					now_point.color = colours[sort];

					now_point.draw_big_point(*render, 5);

					if(i > 0) {
						Vector vector(last_point, now_point);
						vector.draw(*render, now_point.color);
					}

					last_point = now_point;
				}
			}

			text->draw(render, texture, screen);
		}
	}

	void update_point(const SORTING sorting, const int x, const int new_y) {
		coords[(int)sorting][x / X_SCALE].y = new_y;
		coords[(int)sorting][x / X_SCALE].x = x / X_SCALE;

		Point now_point = {};
		Point left_down_corner = rect->get_left_down_corner();

		now_point.x = left_down_corner.x + rect->get_width() / X_SCALE * coords[(int)sorting][x / X_SCALE].x;

		if(coords[(int)sorting][x / X_SCALE].y != 0)
			now_point.y = left_down_corner.y - rect->get_height() * (coords[(int)sorting][x / X_SCALE].y) / Y_SCALE;
		else
			now_point.y = left_down_corner.y;
	}
};

#endif