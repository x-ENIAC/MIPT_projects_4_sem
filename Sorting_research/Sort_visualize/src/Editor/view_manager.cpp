#include "view_manager.h"
#include "../graph_bar.h"
#include "../app.h"

View_manager::View_manager(const Point par_point, const double par_width, const double par_height, const Colour par_color) :
  View_object(par_point, par_width, par_height, LIGHT_GREY, Widget_types::VIEW_MANAGER) {

  	printf("[View_manager] start construct\n");
	count_of_view_objects = 1;

	view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS];
	for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
		view_objects[i] = new View_object;

	who_is_active = -1;

	mouse_click_state = Mouse_click_state::MOUSE_UP;

	printf("[View_manager] start create Pencil\n");
	pencil = new Pencil();

	printf("[View_manager] start create Number_container\n");
	number_container = new Number_container(100);

	printf("[View_manager] start create Graph_bar\n");
	graph_bar = new Graph_bar(Point(450, 300), 700, 400, WHITE, number_container);
	add_view_object(graph_bar);

	printf("[View_manager] start create Button_manager\n");
	buttons = new Button_manager(Point(350, 600), 300, 60, DARK_GREY_3);

	add_view_object(buttons);
	// printf("[View_manager] fill Button_manager\n");
	fill_button_manager();

	is_running_sorting = false;

	printf("[View_manager] end construct\n");
}

View_manager::~View_manager() {
	printf("Destruct View_manager, %ld\n", count_of_view_objects);

	// for(size_t i = 0; i < count_of_view_objects; ++i)
	// 	delete view_objects[i];
	// delete[] view_objects;

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

void View_manager::fill_button_manager() {
	Point left_up_corner = buttons->rect->get_left_up_corner();
	left_up_corner += Point(70, 30);

	Begin_sort_delegate* delegate = new Begin_sort_delegate(number_container, &is_running_sorting);
	Button* button = new Button(delegate, left_up_corner, RED, 120, 50, "Start");
	buttons->add_view_object(button);
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