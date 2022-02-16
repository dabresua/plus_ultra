#include <gol.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <SDL2/SDL.h>
#include <getopt.h>

using namespace std;

//Screen dimension constants
#define SCREEN_WIDTH  (1200)
#define SCREEN_HEIGHT (600)

#define GOL_PERIOD_MS (50)

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

/**
 * @brief get initial conditions by selected set of rules
 */
unsigned int gol_main_get_rule2initial(rule_set_t rule_set)
{
	switch (rule_set) {
	case rule_set_classic: return 30;
	case rule_set_laberinth1: return 30;
	case rule_set_laberinth2: return 30;
	case rule_set_laberinth3: return 30;
	case rule_set_forest: return 30;
	case rule_set_grow_quick: return 10;
	case rule_set_grow_front1: return 15;
	case rule_set_strange_blood: return 15;
	case rule_set_grow_front2: return 15;
	case rule_set_static_psico1: return 70;
	case rule_set_static_psico2: return 70;
	case rule_set_static_rorschach: return 60;
	case rule_set_static_gotele: return 55;
	case rule_set_amongus: return 50;
	case rule_set_pixelism: return 50;
	case rule_set_amebas: return 70;
	case rule_set_chromosoma1: return 70;
	case rule_set_chromosoma2: return 70;
	case rule_set_chromosoma3: return 70;
	case rule_set_chromosoma4: return 70;
	default: return 0;
	}
}

static void show_usage(std::string name)
{
	std::cerr << "Usage: " << name << " <option(s)> SOURCES"
	          << "Options:\n"
	          << "\t-h,--help\t\tShow this help message\n"
	          << "\t-r,--rule RULE\tSpecify the set of rules"
	          << std::endl;
}

int main(int argc, char* args[])
{
	rule_set_t rule_set = rule_set_t(0);
	bool finish = false;
	while (!finish) {
		//std::cout << "opt " << c << std::endl;
		switch(getopt(argc, args, "r:h")) {
		case 'r':
			rule_set = rule_set_t(atoi(optarg));
			break;
		case 'h':
		default:
			show_usage(args[0]);
			break;
		case -1:
			finish = true;
			break;
		}
	}

	unsigned int prob_ini = gol_main_get_rule2initial(rule_set);
	if (prob_ini == 0) {
		std::cout << "Not a valid (" << rule_set << ") set of rules" << std::endl;
		return 0;
	}

	if(!init()) {
		std::cout << "Failed to initialize" << '\n';
		return -1;
	}

	Gol g(SCREEN_WIDTH/PIXEL_SIZE, SCREEN_HEIGHT/PIXEL_SIZE, rule_set);
	//Gol g(3, 10);
	cout << "w [" << g.getW() << "] h [" << g.getH() << "]" << endl;

	g.set_cell(2,3);
	g.set_cell(0,0);
	g.set_cell(20-1, 30-1);
	//cout << g.to_hex() << endl;
	//cout << g.to_string() << endl;

	g.generate(prob_ini);

	//cout << g.to_hex() << endl;
	//cout << g.to_string() << endl;

	bool quit = false;
	SDL_Event e;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	do {
		start = std::chrono::system_clock::now();
		g.run();
		//cout << g.to_string() << endl;

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		g.paint_screen(gRenderer);

		//Update screen
		SDL_RenderPresent(gRenderer);

		end = std::chrono::system_clock::now();
		int elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>
		                 (end-start).count();

		int sleep_ms = GOL_PERIOD_MS - elapsed_ms;
		if(sleep_ms > 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));

		while(SDL_PollEvent(&e) != 0 ) {
			if (e.type == SDL_QUIT) {
				quit = true;
				std::cout << "Quit" << '\n';
			}
		}
	} while(!quit);

	close();
	g.gc();

	return 0;
}
