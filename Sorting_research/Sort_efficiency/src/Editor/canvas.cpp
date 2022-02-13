#include "canvas.h"

void Canvas::load_picture() {

	SDL_Surface* m_surface = IMG_Load("textures/sun1.png");

	for(int y = 0; y < rect->get_height(); ++y)
		for(int x = 0; x < rect->get_width(); ++x) {
			Uint32 pixel = *((Uint32*) m_surface->pixels + (m_surface->h - y) * m_surface->w + x);
		    Uint8 r, g, b, a;
		    SDL_GetRGBA(pixel, m_surface->format, &r, &g, &b, &a);
		}
}

void Canvas::delete_all() {
	double width  = rect->get_width();
	double height = rect->get_height();

	for(size_t i = 0; i < width; ++i)
		delete[] cells_color[i];
	delete[] cells_color;
}

void Canvas::update_position_from_delta(const Point delta) {
	rect->set_center( rect->get_center() - delta );
}
