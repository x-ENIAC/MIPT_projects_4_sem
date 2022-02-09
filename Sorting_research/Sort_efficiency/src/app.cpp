#include "app.h"
#include <vector>

App* App::app = 0;

void App::initialize(const int width_screen, const int height_screen) {

	SDL_STATUSES status = SDL_OKEY;

	if(SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0) {
		printf("[App::initialize] bad init\n");
		status = BAD_SDL_INIT;
		return;
	}

	if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		printf("[App::initialize] bad init\n");
		status = BAD_SDL_INIT;
		return;
	}

	SDL_CreateWindowAndRenderer(width_screen, height_screen, 0, &window, &render);

	if(!(window)) {
		printf("[App::initialize] Window not create\n");
		status = WINDOW_NOT_CREATE;
		return;
	}

	char* name_font = "courier.ttf";

	TTF_Init();

	screen = SDL_GetWindowSurface(window);

	return;
}

void App::deinitialize() {
	SDL_FreeSurface		(app->screen);
	SDL_DestroyWindow	(app->window);
	SDL_DestroyRenderer	(app->render);
	SDL_DestroyTexture	(app->texture);

	TTF_Quit();
	SDL_Quit();

	delete app->view_manager;
	delete controller;
}

void App::update() {
	begin_era = time(NULL);

	SDL_SetRenderDrawColor(render, screen_color.red, screen_color.green, screen_color.blue, screen_color.alpha);
	SDL_RenderClear(app->render);

	printf("[App] Start initialize the view manager\n");

	controller = new Controller_data_charts(5, 10, 20);
	app->view_manager = new View_manager(Point(width_screen / 2.0, height_screen / 2.0), width_screen, height_screen, screen_color);

	printf("\n\nBEGIN EVENTS CYCLE\n");
	SDL_Event event = {};
	bool is_run = true;
	while(is_run) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT)
				is_run = false;

			else {
				app->view_manager->check_events(&event);
			}
		}

		SDL_SetRenderDrawColor(render, screen_color.red, screen_color.green, screen_color.blue, screen_color.alpha);
		SDL_RenderClear(app->render);

		app->view_manager->draw(&app->render, &app->texture, &app->screen);

		app->view_manager->tick(TIME_DELTA);

		SDL_RenderPresent(app->render);
	}
}

SDL_Renderer* App::get_render() {
	return app->render;
}

App* App::get_app() {
	if(!app)
		app = new App();
	return app;
}

void App::remove_app() {
	delete app;
}

long long App::get_begin_era() {
	return begin_era;
}

long long App::get_width_screen() {
	return width_screen;
}

long long App::get_height_screen() {
	return height_screen;
}

Controller_data_charts* App::get_controller() {
	return controller;
}

View_manager* App::get_view_manager() {
	return view_manager;
}
