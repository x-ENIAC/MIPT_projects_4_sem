#ifndef GRAPH_BAR_H
#define GRAPH_BAR_H

#include <unistd.h>
#include <vector>
#include "../GUI/view.h"
#include "../Utils/rectangle.h"
#include "../Math_structures/number_container.h"
#include "../Math_structures/sorts.h"
#include "../Math_structures/sort_manager.h"

class Graph_bar : public View_object {
  public:
	Number_container* number_container;
	int* heights;
	Colour* colours;
	int* number_of_sort;

	Graph_bar(const Point par_point, const double par_width, const double par_height, const Colour par_color, 
				Number_container* arg_number_container);

	void fill_heights();

	void update();

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			rect->draw(*render);

			Point now_point = rect->get_left_down_corner();
			int count = number_container->get_count();
			int delta_x = rect->get_width() / count;

			now_point.x += delta_x / 2;
			now_point.y -= heights[0] / 2;

			for(int i = 0; i < count; ++i) {
				Rectangle now_rect(now_point, delta_x, heights[i], colours[i]);
				now_rect.draw(*render);
				now_rect.draw_contour(*render, BLACK);

				now_point.x += delta_x;
				now_point.y += heights[i] / 2;

				if(i + 1 < count)
					now_point.y -= heights[i + 1] / 2;
			}
		}
	}
};

#endif