#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "GUI/view.h"
#include "app.h"
#include "Editor/view_manager.h"

#include "GUI/button.h"

#include "GUI/button_delegate.h"
#include "GUI/text.h"

SDL_Renderer* render;

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 720;
const double DELTA = 0.5;
const double TIME_DELTA = 0.005;


int main() {
	App::get_app()->initialize(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	render = App::get_app()->get_render();

	App::get_app()->update();
	
	App::get_app()->deinitialize();
	App::get_app()->remove_app();

	return 0;
}