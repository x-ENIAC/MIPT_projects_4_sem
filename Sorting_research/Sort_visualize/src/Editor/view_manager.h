//#include "view.h"
//#include "animation_manager.h"
#include "../GUI/button.h"
#include "../GUI/button_manager.h"
#include "canvas.h"
#include "../number_container.h"

// #include "../charts.h"

#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

class Graph_bar;
#include "../graph_bar.h"
#include "../app.h"

class View_manager;
// class Graph_bar;

const int WIDTH_FILE_PANEL_BUTTON = 90;
const int HEIGHT_FILE_PANEL_BUTTON = 20;

const int WIDTH_TOOLS_WIDGET      = 100;
const int HEIGHT_TOOLS_WIDGET     = 100;

const Point CENTER_MANAGER_OF_CANVAS_MANAGERS = Point(600, 600);
const int WIDTH_MANAGER_OF_CANVAS_MANAGERS_WIDGET  = 200; // 340;
const int HEIGHT_MANAGER_OF_CANVAS_MANAGERS_WIDGET = 200; // 200;

class View_manager : public View_object {
  public:
	View_object** view_objects;
	size_t count_of_view_objects;
	int who_is_active;

	Button_manager* panel_buttons_manager;
	Pencil* pencil;

	Mouse_click_state mouse_click_state;

	// Charts* charts;

	Number_container* number_container;
	Graph_bar* graph_bar;
	Button_manager* buttons;

	bool is_running_sorting;

	Point old_pos_mouse, now_pos_mouse;

	View_manager(const Point par_point, const double par_width, const double par_height, const Colour par_color);

	~View_manager();

	void add_view_object(View_object* new_view);

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			rect->draw(*render);

			for(size_t i = 0; i < count_of_view_objects; ++i)
				view_objects[i]->draw(render, texture, screen);
		}
	}

	void check_events(SDL_Event* event);

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		// printf("\n\nview_manager check_click, mouse (%d, %d)\n", (int)mouse_x, (int)mouse_y);

		if(is_active) {

			//printf("click View_manager\n");
			for(int i = count_of_view_objects - 1; i >= 0; --i) {
				if(view_objects[i]->check_click(mouse_x, mouse_y, par_mouse_status)) {
					//set_new_active_object(i);
					// find_not_alive();
					return true;
				}
			}
		}

		return false;
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		//printf("\n\nview_manager check_click\n");

		if(is_active) {

			//printf("click View_manager\n");
			for(int i = count_of_view_objects - 1; i >= 0; --i) {
				if(view_objects[i]->check_motion(old_mouse, now_mouse, par_mouse_status)) {
					return true;
				}
			}
		}

		return false;
	}

	void tick(const double delta_time) override {
		if(is_running_sorting)
			graph_bar->update();
	}

	bool check_tap(SDL_Event* event);

	void fill_button_manager();

	Number_container* get_number_container();

	Graph_bar* get_graph_bar();
};

#endif