#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <SDL2/SDL.h>
#include <screen_opening.h>

using namespace std;

//Screen dimension constants
#define SCREEN_WIDTH  (1200)
#define SCREEN_HEIGHT (600)

#define MAIN_PERIOD_MS (50)

/* ---- Private API ---- */
SDL_Window* gWindow = NULL;     //The window we'll be rendering to
SDL_Renderer* gRenderer = NULL; //The window renderer

/**
 * @brief: Starts up SDL and creates window
 */
static bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
		cout << "SDL could not initialize! SDL Error: "
		     << SDL_GetError()
		     << endl;
		success = false;
	} else {
		//Set texture filtering to linear
		if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			cout << "Warning: Linear texture filtering not enabled!" << endl;
		}

		//Create window
		gWindow = SDL_CreateWindow("Game of life", SDL_WINDOWPOS_UNDEFINED,
		                           SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
		                           SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			cout << "Window could not be created! SDL Error: "
			     << SDL_GetError()
			     << endl;
			success = false;
		} else {
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1,
			                               SDL_RENDERER_ACCELERATED);
			if( gRenderer == NULL ) {
				cout << "Renderer could not be created! SDL Error: "
				     << SDL_GetError()
				     << endl;
				success = false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
}

/**
 * @brief Frees media and shuts down SDL
 */
void close()
{
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main()
{
	if(!init()) {
		std::cout << "Failed to initialize" << '\n';
		return -1;
	}

	Screen_opening op{1};
	Screen* screen_list[1] = {&op};
	uint8_t actual_screen = 1;
	bool quit = false;
	SDL_Event e;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	do {
		start = std::chrono::system_clock::now();
		Screen *screen = screen_list[actual_screen-1];
		screen->run();

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		screen->paint(gRenderer);

		//Update screen
		SDL_RenderPresent(gRenderer);

		end = std::chrono::system_clock::now();
		int elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>
		                 (end-start).count();

		int sleep_ms = MAIN_PERIOD_MS - elapsed_ms;
		if(sleep_ms > 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));

		if (SDL_PollEvent(&e) != 0 ) {
			if (e.type == SDL_QUIT) {
				quit = true;
				std::cout << "Quit" << '\n';
			} else {
				screen->event(&e);
			}
		}
	} while(!quit);

	close();

	return 0;
}
