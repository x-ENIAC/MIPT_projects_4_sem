//#include "view_manager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "button_delegate.h"
#include "view.h"
#include "../sorts.h"

#ifndef OBJECT_DELEGATES_H
#define OBJECT_DELEGATES_H

#include "../app.h"
#include "../Controller/controller.h"
extern SDL_Renderer* render;

extern const double TIME_DELTA;

const Point CENTER_OF_SPAWN_CANVASES = Point(300, 500);
const double DEFAULT_WIDTH = 100;
const double DEFAULT_HEIGHT = 100;

class Show_points_delegate : public Button_delegate {
  public:
  	bool* is_visible;
  	int index;

  	Show_points_delegate(bool* arg_is_visible, const int arg_index);

  	void click_reaction(const double mouse_x, const double mouse_y) override  {

  		// std::vector<Number> v;
  		int count_of_operations = App::get_app()->get_controller()->get_count_of_operations();
  		int step 				= App::get_app()->get_controller()->get_step();
  		int start_len 			= App::get_app()->get_controller()->get_start_len();

  		//------------------------------------------------------------------
		int cur_len = start_len;

		for(int i = 0; i < count_of_operations; ++i) {
	  		graph_pair pair = {};


	  		App::get_app()->get_controller()->start_research(i, cur_len, index, &pair);
	  		cur_len += step;
			App::get_app()->get_view_manager()->update_charts(pair);

			assignments = 0;
			comparisons = 0;
	  	}
	  		
  		printf("..............................%d\n", count_of_operations);
		
		is_visible[index] = 1 - is_visible[index];
	}

  	void motion_reaction(const double mouse_x, const double mouse_y) override {}

  	void reactive_reaction(Point old_mouse, Point now_mouse) override {}
};




#endif