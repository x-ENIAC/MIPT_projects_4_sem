#include <SDL2/SDL.h>
#include "../Utils/point.h"
#include "../Utils/colour.h"
#include "../Utils/rectangle.h"
#include "../GUI/view.h"
#include "../GUI/button_delegates.h"
#include "pencil.h"
	
#ifndef CANVAS_H
#define CANVAS_H

class Canvas;

// #include "../app.h"

struct Cell {
	Colour color;
	size_t thickness;

	Cell() {
		color = WHITE;
		thickness = 0;
	}

	Cell(const Colour par_color, const size_t par_thickness) {
		color = par_color;
		thickness = par_thickness;
	}

	Colour get_color() {
		return color;
	}

	void set_color(const Colour new_color) {
		color = new_color;
	}
};

class Canvas : public View_object {
  public:
	Pencil* pencil;

	Cell** cells_color;

	Canvas() : View_object() {}

	Canvas(const Point par_point, const double par_width, const double par_height, const Colour par_button_color,
			Pencil* par_pencil) :
	  View_object(par_point, par_width, par_height, par_button_color, Widget_types::CANVAS) {

		cells_color = new Cell*[(int)par_width + 1];

		for(size_t i = 0; i <= par_width; ++i)
			cells_color[i] = new Cell[(int)par_height + 1];

		for(size_t i = 0; i <= par_width; ++i)
			for(size_t j = 0; j <= par_height; ++j) {
				cells_color[i][j].color = par_button_color;
				cells_color[i][j].thickness = 24;
			}

		pencil = par_pencil;
	}

	void load_picture();

	~Canvas() {
		int width = rect->get_width();

		for(int i = 0; i < width; ++i)
			free(cells_color[i]);
		free(cells_color);
	}


	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		if(is_active) {
			if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
				if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
                    Point left_up_corner(rect->get_center().x - rect->width / 2, rect->get_center().y - rect->height / 2);
                    cells_color[(int)(mouse_x - left_up_corner.x)][(int)(mouse_y - left_up_corner.y)].color     = pencil->get_color();
                    cells_color[(int)(mouse_x - left_up_corner.x)][(int)(mouse_y - left_up_corner.y)].thickness = pencil->get_thickness();
					return true;
				}
			}
		}

		return false;
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		if(is_active) {
			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN_AND_MOTION) {
				if(rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y) )) {
					if(rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y) )) {
						Point left_up_corner(rect->get_center().x - rect->width / 2, rect->get_center().y - rect->height / 2);
						cells_color[(int)(now_mouse.x - left_up_corner.x)][(int)(now_mouse.y - left_up_corner.y)].color 	= pencil->get_color();
						cells_color[(int)(now_mouse.x - left_up_corner.x)][(int)(now_mouse.y - left_up_corner.y)].thickness = pencil->get_thickness();
						return true;
					}
				}
			}
		}

		return false;
	}    

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			rect->draw(*render);

			Point left_up_corner(rect->get_center().x - rect->width / 2, rect->get_center().y - rect->get_height() / 2);

			for(size_t i = 0; i <= rect->width; ++i)
				for(size_t j = 0; j <= rect->height; ++j) {
                    Point new_point(i + left_up_corner.x, j + left_up_corner.y, cells_color[i][j].color);

                    if(cells_color[i][j].color != color) {
                        Rectangle new_rect(new_point, pencil->get_thickness() / 2.0, pencil->get_thickness() / 2.0, cells_color[i][j].color, false);
                        new_rect.draw(*render);
                    } else
                        new_point.draw_point(*render);
				}
		}
	}

	void delete_all();

	void update_position_from_delta(const Point delta);
};

#endif


