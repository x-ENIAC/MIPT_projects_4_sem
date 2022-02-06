//#include "view.h"
//#include "animation_manager.h"
#include "../GUI/button.h"
#include "../GUI/button_manager.h"
#include "canvas.h"
#include "../charts.h"

#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include "../app.h"

class View_manager;

class Create_new_canvas_delegate;

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

	// Manager_of_canvas_managers* manager_of_canvas_managers;

	// Painter_tools_and_plugins* painter_tools_and_plugins;

	Mouse_click_state mouse_click_state;

	// Chart* comparison_chart;
	// Chart* assignment_chart;
	Charts* charts;

	Button_manager* buttons;

	Point old_pos_mouse, now_pos_mouse;

	View_manager(const Point par_point, const double par_width, const double par_height, const Colour par_color) :
	  View_object(par_point, par_width, par_height, LIGHT_GREY, Widget_types::VIEW_MANAGER) {

	  	printf("start View_manager\n");
		count_of_view_objects = 1;

		printf("create objects\n");
		view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS];
		for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
			view_objects[i] = new View_object;

		who_is_active = -1;

		mouse_click_state = Mouse_click_state::MOUSE_UP;

		printf("new pencil\n");
		pencil = new Pencil();

		printf("charts\n");
		charts = new Charts(Point(400, 200), 700, 700, pencil, COUNT_OF_SORTS);
		printf("add chart\n");
		add_view_object(charts);

		printf("create button_manager\n");
		buttons = new Button_manager(Point(350, 600), 300, 60, DARK_GREY_3);

		add_view_object(buttons);
		printf("fill button_manager\n");
		fill_button_manager();

		printf("end construct view manager\n");
	}

	~View_manager() {
		printf("Destruct View_manager, %ld\n", count_of_view_objects);

		// for(size_t i = 0; i < count_of_view_objects; ++i)
		// 	delete view_objects[i];
		// delete[] view_objects;

		// delete panel_buttons_manager;
		// delete manager_of_canvas_managers;

		count_of_view_objects = 0;
		who_is_active = 0;
	}

	void add_view_object(View_object* new_view) {
		view_objects[count_of_view_objects] = new_view;
		++count_of_view_objects;

		++widget_types[(int)new_view->get_yourself_type()];
	}  	

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			rect->draw(*render);

			for(size_t i = 0; i < count_of_view_objects; ++i) {
				view_objects[i]->draw(render, texture, screen);
			}

			// tool_manager->draw(render, texture, screen);
		}
	}

	void check_events(SDL_Event* event) {
		double x_mouse = event->button.x, y_mouse = event->button.y;

		//printf("%d\n", event->type);
		if(event->type == SDL_MOUSEBUTTONUP) {
			mouse_click_state = Mouse_click_state::MOUSE_UP;

			bool is_solved = check_click(x_mouse, y_mouse, &mouse_click_state);
		}

		else
		if(event->type == SDL_MOUSEBUTTONDOWN) {
			mouse_click_state = Mouse_click_state::MOUSE_DOWN;
			

			bool is_solved = check_click(x_mouse, y_mouse, &mouse_click_state);
		}		

		else if(event->type == SDL_MOUSEMOTION) {

			if(mouse_click_state == Mouse_click_state::MOUSE_DOWN || mouse_click_state == Mouse_click_state::MOUSE_DOWN_AND_MOTION) {
				mouse_click_state = Mouse_click_state::MOUSE_DOWN_AND_MOTION;
				//bool is_solved = check_motion(old_pos_mouse, now_pos_mouse, &mouse_click_state);

			} else 
				mouse_click_state = Mouse_click_state::MOUSE_MOTION;
				// printf("motion\n");

			now_pos_mouse = {x_mouse, y_mouse};
			bool is_solved = check_motion(old_pos_mouse, now_pos_mouse, &mouse_click_state);
			old_pos_mouse = now_pos_mouse;
			
		}

		else if(event->type == SDL_KEYDOWN) {
			bool is_solved = check_tap(event);
		}
	}

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

		// find_not_alive();
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

	bool check_tap(SDL_Event* event) {
		return false;
	}

	void update_charts(graph_pair &pair) {
		charts->update_point(pair);
	}

	void fill_button_manager() {
		Point left_up_corner = buttons->rect->get_left_up_corner();
		left_up_corner += Point(30, 30);

		for(int i = 0; i < COUNT_OF_SORTS; ++i) {
			Show_points_delegate* delegate = new Show_points_delegate(charts->is_visible, i);
			Button* button = new Button(delegate, left_up_corner, charts->colours[i], 50, 50);
			buttons->add_view_object(button);

			left_up_corner += Point(60, 0);
		}
	}
};

#endif