#include "view_manager.h"
#include "../app.h"

View_manager::View_manager(const Point par_point, const double par_width, const double par_height, const Colour par_color) :
  View_object(par_point, par_width, par_height, LIGHT_GREY, Widget_types::VIEW_MANAGER) {

	printf("[View_manager::construct] start View_manager\n");
	count_of_view_objects = 1;

	printf("[View_manager::construct] create objects\n");
	view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS];
	for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
		view_objects[i] = new View_object;

	who_is_active = -1;

	mouse_click_state = Mouse_click_state::MOUSE_UP;

	printf("[View_manager::construct] new pencil\n");
	pencil = new Pencil();

	printf("[View_manager::construct] charts\n");
	charts = new Charts(Point(400, 200), 700, 700, pencil, COUNT_OF_SORTS);
	printf("[View_manager::construct] add chart %p\n", charts);
	add_view_object(charts);

	printf("[View_manager::construct] create button_manager\n");
	buttons = new Button_manager(Point(400, 580), 250, 240, DARK_GREY_3);

	add_view_object(buttons);
	printf("[View_manager::construct] fill button_manager\n");
	fill_button_manager();

	printf("[View_manager::construct] end construct view manager\n");
	printf("[View_manager::construct] add chart %p\n", charts);
}

View_manager::~View_manager() {
	printf("Destruct View_manager, %ld\n", count_of_view_objects);

	for(size_t i = 0; i < count_of_view_objects; ++i)
		delete view_objects[i];
	delete[] view_objects;

	count_of_view_objects = 0;
	who_is_active = 0;
}


void View_manager::add_view_object(View_object* new_view) {
	view_objects[count_of_view_objects] = new_view;
	++count_of_view_objects;

	++widget_types[(int)new_view->get_yourself_type()];
	// printf("add chart %p\n", charts);
}

void View_manager::check_events(SDL_Event* event) {
	// printf("add chart %p\n", charts);
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
	left_up_corner += Point(125, 30);

	for(int i = 0; i < COUNT_OF_SORTS; ++i) {
		Show_points_delegate* delegate = new Show_points_delegate(charts->is_visible, i);
		Button* button = new Button(delegate, left_up_corner, charts->colours[i], 230, 40, text_sorts[i]);
		buttons->add_view_object(button);

		left_up_corner += Point(0, 45);
	}
}

bool View_manager::check_tap(SDL_Event* event) {
	return false;
}



void View_manager::update_charts(graph_pair pairs) {
	// printf("UPDATEEEEEEEEEEEEEEEEEEEEEEEEEe\n");
	// printf("%p\n", charts);
	charts->update_point(pairs);
	// printf("%d %d %d %d\n", pairs.assign, pairs.compare, pairs.sorting, pairs.len_array);
	// printf("%p\n", charts);
}