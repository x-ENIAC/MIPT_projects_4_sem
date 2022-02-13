#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../Utils/point.h"
#include "../Utils/colour.h"
#include "../Utils/rectangle.h"
#include "../Editor/widget_types.h"

#ifndef VIEW_H
#define VIEW_H

const char NON_PATH_TO_PUCTURE[] = "non_picture";


const int MAX_COUNT_OF_VIEW_OBJECTS = 30;
const int DELTA_BETWEEN_BUTTONS = 5;

const int WIDTH_CLOSE_BUTTON  = 20;
const int HEIGHT_CLOSE_BUTTON = 20;
const int WIDTH_TABS_BUTTON = 150;
const int HEIGHT_TABS_BUTTON = 20;
const int ICON_PLUGIN_SIZE = 50;

extern SDL_Renderer* render;

#ifndef CONSTANTS
#define CONSTANTS

static  char TEXT_SPACE[] = " ";
static  char TEXT_CLOSE[] = "x";
static  char TEXT_ROLL_UP[] = "-";
static  char TEXT_TITLE[] = "Title";
static  char TEXT_FILE[] = "File";
static  char TEXT_NEW[] = "New";
static  char TEXT_HELP[] = "Help";
static  char TEXT_PALETTE_1[] = "Palette 1";
static  char TEXT_PALETTE_2[] = "Palette 2";
static  char TEXT_SPLINE[]	  = "Spline";
static  char TEXT_CANVASES[]  = "Canvases";

#endif

enum class Mouse_click_state {
	MOUSE_MOTION			= 1,
	MOUSE_DOWN 				= 2,
	MOUSE_DOWN_AND_MOTION	= 3,
	MOUSE_UP				= 4,
};

class View_object {
	public:
	Colour color;

	Rectangle* rect;
	int* widget_types;
	Widget_types yourself_type;

	bool is_visible;
	bool is_active;
	bool is_alive;
	bool is_reactive;

	View_object(const Widget_types par_widget_types = Widget_types::VIEW_OBJECT,
				const char par_path_to_picture[] = NON_PATH_TO_PUCTURE) {
		
		color = {0, 0, 0, 0};

		rect = new Rectangle;

		widget_types = new int[COUNT_OF_TYPES];

		for(size_t i = 0; i < COUNT_OF_TYPES; ++i)
			widget_types[i] = 0;

		yourself_type = par_widget_types;

		is_visible = is_active = is_alive = is_reactive = true;
	}

	View_object(const Point par_center, const double par_width, const double par_height,
				const Colour par_color, const Widget_types par_widget_types = Widget_types::VIEW_OBJECT,
				const char par_path_to_picture[] = NON_PATH_TO_PUCTURE) {

		color = par_color;

		rect = new Rectangle(par_center, par_width, par_height, par_color, false);

		widget_types = new int[COUNT_OF_TYPES];

		for(size_t i = 0; i < COUNT_OF_TYPES; ++i)
			widget_types[i] = 0;

		yourself_type = par_widget_types;

		is_visible = is_active = is_alive = true;
	}

	~View_object() {
		delete rect;
		delete[] widget_types;
	}

	virtual void draw(SDL_Renderer** render, SDL_Texture** par_texture, SDL_Surface** screen) {
		if(is_visible) {
			rect->draw(*render);
		}
	}

	virtual bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) {return false;}

	virtual bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) {return false;}

	Widget_types get_yourself_type() const {
		return yourself_type;
	}

	void delete_all() {
		printf("begin View_object delete_all\n");

		delete rect;
		delete[] widget_types;

		is_visible = is_active = false;
		is_alive = false;

		printf("end VIEW_OBJECT delete_all\n");
	}

	virtual void update_position_from_delta(Point delta) {
		rect->set_center(rect->get_center() - delta);     
	}

	virtual void update_view_object_position(const double mouse_x, const double mouse_y) {}

	virtual void tick(const double delta_time) {}
};

#endif