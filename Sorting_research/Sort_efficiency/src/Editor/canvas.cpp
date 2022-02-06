#include "canvas.h"

void Canvas::load_picture() {

	printf("???????????\n");
	SDL_Surface* m_surface = IMG_Load("textures/sun1.png");

 	// void *target_pixel = ((Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);

	// void* mPixels;
	// int mPitch;

	// SDL_Texture* ntexture = IMG_LoadTexture(render, "textures/sun1.png");
	// SDL_LockTexture( ntexture, NULL, &mPixels, &mPitch );
	printf("here\n");

	// printf("!!! inage %d, %d\n", ntexture->w, ntexture->h);
	for(int y = 0; y < rect->get_height(); ++y)
		for(int x = 0; x < rect->get_width(); ++x) {
			printf("!!!!\n");
			Uint32 pixel = *((Uint32*) m_surface->pixels + (m_surface->h - y) * m_surface->w + x);
			printf("@@@\n");
		    Uint8 r, g, b, a;
		    printf(".......\n");
		    SDL_GetRGBA(pixel, m_surface->format, &r, &g, &b, &a);
			printf("i = %d, j = %d\n", x, y);
			// cells_color[i][j].begin_color =
			// cells_color[i][j].color_after_correction = *((Colour*)mPixels);
			// cells_color[i][j].begin_color.print();
			// ++mPixels;
		}

	// SDL_UnlockTexture(ntexture);
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
