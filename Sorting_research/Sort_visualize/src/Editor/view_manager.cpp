#include "view_manager.h"
#include "../Sorting_visualization/graph_bar.h"
#include "../app.h"

View_manager::View_manager(const Point par_point, const double par_width, const double par_height, const Colour par_color) :
  View_object(par_point, par_width, par_height, LIGHT_GREY, Widget_types::VIEW_MANAGER) {

	count_of_view_objects = 1;

	view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS];
	for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
		view_objects[i] = new View_object;

	who_is_active = -1;

	mouse_click_state = Mouse_click_state::MOUSE_UP;

	pencil = new Pencil();

	number_container = new Number_container(25);

	graph_bar = new Graph_bar(Point(460, 300), 700, 400, WHITE, number_container);
	add_view_object(graph_bar);

	buttons = new Button_manager(Point(460, 600), 270, 180, BLUE);

	add_view_object(buttons);
	fill_button_manager();

	is_running_sorting = false;
}

View_manager::~View_manager() {
	count_of_view_objects = 0;
	who_is_active = 0;
}


void View_manager::add_view_object(View_object* new_view) {
	view_objects[count_of_view_objects] = new_view;
	++count_of_view_objects;

	++widget_types[(int)new_view->get_yourself_type()];
}

void View_manager::check_events(SDL_Event* event) {
	double x_mouse = event->button.x, y_mouse = event->button.y;

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

		} else 
			mouse_click_state = Mouse_click_state::MOUSE_MOTION;

		now_pos_mouse = {x_mouse, y_mouse};
		bool is_solved = check_motion(old_pos_mouse, now_pos_mouse, &mouse_click_state);
		old_pos_mouse = now_pos_mouse;
		
	}

	else if(event->type == SDL_KEYDOWN) {
		bool is_solved = check_tap(event);
	}
}

void View_manager::fill_button_manager() {
	Point left_up_corner = buttons->rect->get_left_up_corner();
	left_up_corner += Point(70, 30);

	Begin_sort_delegate* delegate_begin = new Begin_sort_delegate(number_container, &is_running_sorting);
	Button* button_start = new Button(delegate_begin, left_up_corner, YELLOW, 120, 50, "Start");
	buttons->add_view_object(button_start);

	left_up_corner += Point(130, 0);

	Stop_sort_delegate* delegate_stop = new Stop_sort_delegate(number_container, &is_running_sorting);
	Button* button_stop = new Button(delegate_stop, left_up_corner, YELLOW, 120, 50, "Stop");
	buttons->add_view_object(button_stop);

	left_up_corner += Point(-130, 60);

	Choose_sort_delegate* bubble_sort_delegate = new Choose_sort_delegate(get_graph_bar()->number_of_sort, SORTING::BUBBLE_SORT);
	Button* bubble_sort_button = new Button(bubble_sort_delegate, left_up_corner, YELLOW, 120, 50, "Bubble");
	buttons->add_view_object(bubble_sort_button);

	left_up_corner += Point(130, 0);

	Choose_sort_delegate* insert_sort_delegate = new Choose_sort_delegate(get_graph_bar()->number_of_sort, SORTING::INSERT_SORT);
	Button* insert_sort_button = new Button(insert_sort_delegate, left_up_corner, YELLOW, 120, 50, "Insert");
	buttons->add_view_object(insert_sort_button);

	left_up_corner += Point(-130, 60);

	Refresh_array_delegate* refresh_array_delegate = new Refresh_array_delegate(number_container);
	Button* refresh_array_button = new Button(refresh_array_delegate, left_up_corner, YELLOW, 120, 50, "Refresh");
	buttons->add_view_object(refresh_array_button);
}

bool View_manager::check_tap(SDL_Event* event) {
	return false;
}

Number_container* View_manager::get_number_container() {
	return number_container;
}

Graph_bar* View_manager::get_graph_bar() {
	return graph_bar;
}