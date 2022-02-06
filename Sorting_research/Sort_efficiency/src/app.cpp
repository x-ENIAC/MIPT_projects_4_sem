#include "app.h"
// #include "sorts.h"
// #include "number.h"
#include <vector>

App* App::app = 0;

void App::initialize(const int width_screen, const int height_screen) {

	SDL_STATUSES status = SDL_OKEY;

	if(SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0) {
		printf("bad init\n");
		status = BAD_SDL_INIT;
		return;
	}

	if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		printf("bad init\n");
		status = BAD_SDL_INIT;
		return;
	}

	SDL_CreateWindowAndRenderer(width_screen, height_screen, 0, &window, &render);

	if(!(window)) {
		printf("Window not create\n");
		status = WINDOW_NOT_CREATE;
		return;
	}

	char* name_font = "courier.ttf";

	TTF_Init();

	screen = SDL_GetWindowSurface(window);

	return;
}

void App::deinitialize() {
	SDL_FreeSurface    (app->screen);
	SDL_DestroyWindow  (app->window);
	SDL_DestroyRenderer(app->render);
	SDL_DestroyTexture (app->texture);

	TTF_Quit();
	SDL_Quit();

	delete app->view_manager;
}

void fill_random_values(Number* numbers, const int len) {
	for(int i = 0; i < len; ++i) {
		numbers[i].value = rand() % 100001;
		numbers[i].pos = i;
	}
}

void App::update() {
	begin_era = time(NULL);

	SDL_SetRenderDrawColor(render, screen_color.red, screen_color.green, screen_color.blue, screen_color.alpha);
	SDL_RenderClear(app->render);

	printf("Start initialize the view manager\n");
	// app->plugin_manager = new Plugin_manager();

	app->view_manager = new View_manager(Point(width_screen / 2.0, height_screen / 2.0), width_screen, height_screen, screen_color);

	//-------------------------------------------------------------
	for(int len = 5; len <= MAX_LEN; len += 5) {


		for(int sort = 0; sort < 5; ++sort) {
			int comparisons = 0;
			int assignments = 0;

			Number* numbers = new Number[len];
			fill_random_values(numbers, len);

			graph_pair pair = {};
			// printf("begin %s\n", text_sorts[sort]);
			standartized_sorts[sort](numbers, len, &pair);
			// printf("%d %d %d %d\n", pair.sorting, pair.assign, pair.compare, pair.len_array);
			app->view_manager->update_charts(pair);
			// printf("\n\n");

			delete[] numbers;
		}



		// graph_pair bubble_pairs = bubble_sort(numbers, len); //get_sort_pairs(numbers, len);
		// graph_pair choose_pairs = choose_sort(numbers, len);
		// graph_pair insert_pairs = insert_sort(numbers, len);
		// graph_pair std_pairs = std_sort(numbers, len);
		// graph_pair std_stable_pairs = std_stable_sort(numbers, len);
		// // for(int i = 0; i < len; ++i)
		// // 	printf("%d %d\n", pairs[i].assign, pairs[i].compare);
		// // printf("%d %d %d %d\n", bubble_pairs.sorting, bubble_pairs.assign, bubble_pairs.compare, bubble_pairs.len_array);

		// app->view_manager->update_charts(bubble_pairs);
		// app->view_manager->update_charts(choose_pairs);
		// app->view_manager->update_charts(insert_pairs);
		// app->view_manager->update_charts(std_pairs);
		// app->view_manager->update_charts(std_stable_pairs);
	}
	//-------------------------------------------------------------

	for(int i = 0; i < COUNT_OF_SORTS; ++i) {
		Text* text = new Text(Point(750, 500 + i * 30), text_sorts[i], 50, 10, app->view_manager->charts->colours[i]);
		app->view_manager->add_view_object(text);
	}

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

// Canvas* App::get_active_canvas() {
// 	return (Canvas*)(App::get_app()->get_view_manager()->manager_of_canvas_managers->active_canvas->view_objects[0]);
// }

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

View_manager* App::get_view_manager() {
	return view_manager;
}
