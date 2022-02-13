#include <SDL2/SDL.h>
#include "../Utils/point.h"
#include "../Utils/colour.h"
#include "../Utils/rectangle.h"
#include "text.h"
#include "button_delegate.h"
#include "button_delegates.h"
#include "view.h"

#ifndef BUTTON_H
#define BUTTON_H

const size_t MAX_COUNT_OF_VIEW_OBJECTS_FOR_BUTTON = 5;

class Button : public View_object {
  public:
	Button_delegate* delegate;

	View_object** view_objects;
	size_t count_of_views;

	Button() : View_object(Widget_types::BUTTON) {

		view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS_FOR_BUTTON];

		for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS_FOR_BUTTON; ++i)
			view_objects[i] = new View_object;
		count_of_views = 0;
	}	

	Button(Button_delegate* par_delegate, const Point par_point, const Colour par_button_color, const double par_width, const double par_height, 
								const char text_on_button[] = TEXT_SPACE, const Colour par_text_color = BLACK, const char* par_path_to_picture = NON_PATH_TO_PUCTURE) :
	  View_object (par_point, par_width, par_height, par_button_color, Widget_types::BUTTON, par_path_to_picture) {

		delegate = par_delegate;


		view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS_FOR_BUTTON];
		for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS_FOR_BUTTON; ++i)
			view_objects[i] = new View_object;
		count_of_views = 0;

		Point text_center = par_point;

		Text* text = new Text(text_center, text_on_button, par_width, par_height, par_text_color);
		view_objects[count_of_views++] = text;
		is_visible = true;
	}

	~Button() {
		printf("~Button\n");
		delete delegate;

		for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS_FOR_BUTTON; ++i)
			delete[] view_objects[i];

		delete[] view_objects;

		count_of_views = 0;
	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {

			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN) {
				delegate->click_reaction(mouse_x, mouse_y);
			}

			return true;
		}

		return false;
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		if(rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y) )) {
			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN_AND_MOTION)
				delegate->motion_reaction(now_mouse.x, now_mouse.y);

			else
			if(*par_mouse_status == Mouse_click_state::MOUSE_MOTION)
				delegate->reactive_reaction(old_mouse, now_mouse);				

			return true;
		}

		return false;
	}	

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			rect->draw(*render);

			for(size_t i = 0; i < count_of_views; ++i)
				view_objects[i]->draw(render, texture, screen);
		}
	}

	void update_center_position(const Point new_center) {
		Point old_center(rect->get_center());

		rect->set_center(new_center);

		for(size_t i = 0; i < count_of_views; ++i) {
			Point new_view_center(view_objects[i]->rect->get_center());

			new_view_center += new_center;
			new_view_center -= old_center;

			view_objects[i]->rect->set_center(new_view_center);
		}
	}


	void update_position_from_delta(const Point delta) {
		Point old_center(rect->get_center());
		Point new_center(old_center);
		new_center -= delta;

		rect->set_center(new_center);

		for(size_t i = 0; i < count_of_views; ++i) {
			Point new_view_center(view_objects[i]->rect->get_center());

			new_view_center -= delta;

			view_objects[i]->rect->set_center(new_view_center);
		}
	}

	void delete_all() {
		printf("begin button delete_all\n");

		for(size_t i = 0; i < count_of_views; ++i) {
			delete[] view_objects[i];
		}

		count_of_views = 0;

		printf("end button delete_all\n");
	}

	
	void tick(const double delta_time) override {
		for(size_t i = 0; i < count_of_views; ++i) {
			if(!(view_objects[i]->is_alive)) {
				printf("Delete!!\n");
			}

			view_objects[i]->tick(delta_time);
		}
	}	
};

#endif


