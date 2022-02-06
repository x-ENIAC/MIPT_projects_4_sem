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




#endif