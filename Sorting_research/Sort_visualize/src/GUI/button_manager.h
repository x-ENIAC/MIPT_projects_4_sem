#include "view.h"
#include "button.h"
#include "../Utils/colour.h"

#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

class Button_manager : public View_object {
  public:
	Button** buttons;
	size_t count_of_buttons;

	Button_manager() : View_object(Widget_types::BUTTON_MANAGER) {
		count_of_buttons = 0;

		buttons = new Button*[MAX_COUNT_OF_VIEW_OBJECTS];
		for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
			buttons[i] = new Button;
	}	

	Button_manager(const Point par_center, const double par_width, const double par_height, const Colour par_color) :
	  View_object(par_center, par_width, par_height, par_color, Widget_types::BUTTON_MANAGER) {
		count_of_buttons = 0;

		buttons = new Button*[MAX_COUNT_OF_VIEW_OBJECTS];
		for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
			buttons[i] = new Button;
	}

	void add_view_object(Button* new_button) {
		buttons[count_of_buttons] = new_button;
		++count_of_buttons;

		++widget_types[int(new_button->get_yourself_type())];
	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		if(rect->is_point_belongs_to_rectangle(mouse_x, mouse_y)) {
			for(size_t i = 0; i < count_of_buttons; ++i) {
				if(buttons[i]->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
					if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN) {
						buttons[i]->delegate->click_reaction(mouse_x, mouse_y);
					}
					return true;
				}
			}
		}

		return false;
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {

		if(rect->is_point_belongs_to_rectangle(now_mouse)) {

			for(size_t i = 0; i < count_of_buttons; ++i) {

				if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN_AND_MOTION) {
					buttons[i]->delegate->motion_reaction(now_mouse.x, now_mouse.y);
				}

				else {
					if(buttons[i]->rect->is_point_belongs_to_rectangle( Point(old_mouse.x, old_mouse.y) ) ||
					   buttons[i]->rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y) )	) {

						buttons[i]->delegate->reactive_reaction(old_mouse, now_mouse);
					}
				}
			}
		}

		return false;
	}		

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		rect->draw(*render);

		for(size_t i = 0; i < count_of_buttons; ++i)
			buttons[i]->draw(render, texture, screen);
	}

	void delete_all() {
		printf("begin Button_manager delete_all\n");

		for(size_t i = 0; i < count_of_buttons; ++i) {
			buttons[i]->delete_all();
			delete[] buttons[i];
		}

		delete[] buttons;
		count_of_buttons = 0;

		printf("end Button_manager delete_all\n");
	}

	void update_position_from_delta(Point delta) {

		for(size_t i = 0; i < count_of_buttons; ++i) {
			buttons[i]->update_position_from_delta(delta);
		}
	}

	inline size_t get_count_of_buttons() const {
		return count_of_buttons;
	}

	void tick(const double delta_time) override {
		for(size_t i = 0; i < count_of_buttons; ++i) {
			if(!(buttons[i]->is_alive)) {
				printf("Delete!!\n");
			}

			buttons[i]->tick(delta_time);
		}
	}
};

#endif