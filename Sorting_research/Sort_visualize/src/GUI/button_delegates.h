//#include "view_manager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "button_delegate.h"
#include "view.h"
#include "../sorts.h"
#include "../graph_bar.h"

#ifndef OBJECT_DELEGATES_H
#define OBJECT_DELEGATES_H

#include "../app.h"
// #include "../Controller/controller.h"
#include "../number_container.h"
extern SDL_Renderer* render;

extern const double TIME_DELTA;

const Point CENTER_OF_SPAWN_CANVASES = Point(300, 500);
const double DEFAULT_WIDTH = 100;
const double DEFAULT_HEIGHT = 100;

class Begin_sort_delegate : public Button_delegate {
  public:
	Number_container* number_container;
	bool* is_running_sorting;

	Begin_sort_delegate(Number_container* arg_number_container, bool* arg_is_running_sorting);

	void click_reaction(const double mouse_x, const double mouse_y) override {
		*is_running_sorting = true;
		// App::get_app()->get_view_manager()->get_graph_bar()->update();
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {}
};


class Stop_sort_delegate : public Button_delegate {
  public:
	Number_container* number_container;
	bool* is_running_sorting;

	Stop_sort_delegate(Number_container* arg_number_container, bool* arg_is_running_sorting);

	void click_reaction(const double mouse_x, const double mouse_y) override {
		*is_running_sorting = false;
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {}
};


class Choose_sort_delegate : public Button_delegate {
  public:
	int* number_of_sort;
	SORTING sorting;

	Choose_sort_delegate(int* arg_number_of_sort, SORTING arg_sorting);

	void click_reaction(const double mouse_x, const double mouse_y) override {
		*number_of_sort = sorting;
		printf("choose %d sort\n", sorting);
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {}
};


class Refresh_array_delegate : public Button_delegate {
  public:
	Number_container* number_container;

	Refresh_array_delegate(Number_container* arg_number_container);

	void click_reaction(const double mouse_x, const double mouse_y) override {
		number_container->fill_container();
		App::get_app()->get_view_manager()->get_graph_bar()->fill_heights();
		App::get_app()->get_sort_manager()->set_i(0);
		App::get_app()->get_sort_manager()->set_j(1);
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {}
};


#endif