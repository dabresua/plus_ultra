#include <gol.h>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <cstring>

#define GOL_DEFAULT_W 10
#define GOL_DEFAULT_H 10

#define CURRENT_WORLD_1 false
#define CURRENT_WORLD_2 true

#define PIXEL_BLANK (0)
#define CELL_SIZE (PIXEL_SIZE - 2*PIXEL_BLANK)

Gol::Gol(unsigned int w, unsigned int h, rule_set_t r)
{
	width = w;
	height = h;
	rule_set = r;
	std::cout << "[" << width << "," << height << "]" << '\n';
	world1 = new bool*[width];
	world2 = new bool*[width];
	for(unsigned int i = 0; i < width; i++) {
		world1[i] = new bool[height];
		world2[i] = new bool[height];
	}
	current_world = CURRENT_WORLD_1;
	screen = screen_gol;
}

void Gol::gc()
{
	for(unsigned int i = 0; i < height; i++) {
		delete[] world1[i];
		delete[] world2[i];
	}
	delete[] world1;
	delete[] world2;
}

void Gol::set_or_clr(Coordinates c, bool set)
{
	if(c.x > width || c.y > height) {
		std::cerr << "Index excedes size" << '\n';
		return;
	}
	if(current_world == CURRENT_WORLD_1) {
		world1[c.x][c.y] = set;
	} else {
		world2[c.x][c.y] = set;
	}
}

std::string Gol::to_string()
{
	std::string str = "";
	bool **c_world = current_world?world2:world1;
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			str+= c_world[j][i]?"x":" ";
		}
		str+="|\n";
	}
	return str;
}

void Gol::paint_screen_gol(SDL_Renderer* gRenderer)
{
	bool **c_world = current_world?world2:world1;
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
	for (int i = 0; i < (int)height; i++) {
		for (int j = 0; j < (int)width; j++) {
			if(c_world[j][i]) {
				SDL_Rect fillRect = { j*PIXEL_SIZE+PIXEL_BLANK,
				                      i*PIXEL_SIZE+PIXEL_BLANK,
				                      CELL_SIZE, CELL_SIZE};
				SDL_RenderFillRect(gRenderer, &fillRect);
			}
		}
	}
}

void Gol::paint_screen_init(SDL_Renderer* gRenderer)
{
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Press any key",
	                                                   {0, 0, 0});
	SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer,
	                                                    surfaceMessage);
	SDL_Rect Message_rect;
	Message_rect.x = width/2-50;
	Message_rect.y = height/2-50;
	Message_rect.w = 100;
	Message_rect.h = 100;
	SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);
}

void Gol::paint_screen(SDL_Renderer* gRenderer)
{
	switch (screen) {
		case screen_init:
			//std::cout<<"Screen init"<<std::endl;
			paint_screen_init(gRenderer);
			break;
		case screen_gol:
			//std::cout<<"Screen gol"<<std::endl;
			paint_screen_gol(gRenderer);
			break;
		default: assert(false);
	}
}

std::string Gol::to_hex()
{
	std::string str = "";
	/* TODO */
	return str;
}

void Gol::generate(int life)
{
	bool **c_world = current_world?world2:world1;
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			/* TODO: use <random> API */
			if ((std::rand() % 100) < life) {
				c_world[j][i] = true;
			} else {
				c_world[j][i] = false;
			}
		}
	}
}

void Gol::inc_life(bool **c_world, unsigned int c, unsigned int r,
                   unsigned int *life)
{
	if(c_world[c][r])
		(*life)++;
}

void Gol::run()
{
	bool **c_world = current_world?world2:world1;
	bool **c_world2 = current_world?world1:world2;
	for (size_t r = 0; r < height; r++) {
		for (size_t c = 0; c < width; c++) {
			//std::cout << "[" << c << "," << r << "] is " << get_status(r, c) << '\n';
			unsigned int cell_r = r;
			unsigned int cell_c = c;
			bool lives = c_world[c][r];
			unsigned int life = 0;
			// TODO: export to a function
			// TODO: different world shapes
			if(r > 0) {
				r--;
				if(c > 0) {
					c--;
					inc_life(c_world, c, r, &life);
					c++;
				}
				inc_life(c_world, c, r, &life);
				if(c < (width - 1)) {
					c++;
					inc_life(c_world, c, r, &life);
				}
				c = cell_c;
				r = cell_r;
			}
			if(c > 0) {
				c--;
				inc_life(c_world, c, r, &life);
				c++;
			}
			if(c < (width - 1)) {
				c++;
				inc_life(c_world, c, r, &life);
			}
			c = cell_c;
			if(r < (height - 1) ) {
				r++;
				if(c > 0) {
					c--;
					inc_life(c_world, c, r, &life);
					c++;
				}
				inc_life(c_world, c, r, &life);
				if(c < (width - 1)) {
					c++;
					inc_life(c_world, c, r, &life);
				}
				c = cell_c;
				r = cell_r;
			}
			//std::cout << "cell " << lives << " [" << c << "," << r << "] is " << life << '\n';

			// TODO: Export to a function
			// TODO: different set of rules
			switch(rule_set) {
			case rule_set_classic:
				c_world2[c][r] = lives ? life >= 2 && life <= 3 : life == 3;
				break;
			case rule_set_laberinth1:
				c_world2[c][r] = lives ? life >= 2 && life <= 4 : life == 3;
				break;
			case rule_set_laberinth2:
				c_world2[c][r] = lives ? life >= 2 && life <= 4 : life == 2;
				break;
			case rule_set_laberinth3:
				c_world2[c][r] = lives ? life >= 1 && life <= 3 : life == 2;
				break;
			case rule_set_forest:
				c_world2[c][r] = lives ? life >= 3 && life <= 5 : life == 2;
				break;
			case rule_set_grow_quick:
				c_world2[c][r] = lives ? life >= 3 && life <= 5 : life == 3;
				break;
			case rule_set_grow_front1:
				c_world2[c][r] = lives ? life >= 4 && life <= 6 : life >= 3;
				break;
			case rule_set_strange_blood:
				c_world2[c][r] = lives ? life >= 4 : life >= 3;
				break;
			case rule_set_grow_front2:
				c_world2[c][r] = lives ? life >= 4 && life <= 7 : life >= 3;
				break;
			case rule_set_static_psico1:
				c_world2[c][r] = lives ? life >= 4 : life >= 9;
				break;
			case rule_set_static_psico2:
				c_world2[c][r] = lives ? life >= 4 : life >= 8;
				break;
			case rule_set_static_rorschach:
				c_world2[c][r] = lives ? life >= 4 : life >= 7;
				break;
			case rule_set_static_gotele:
				c_world2[c][r] = lives ? life >= 4 : life >= 6;
				break;
			case rule_set_amongus:
				c_world2[c][r] = lives ? life >= 4 : life >= 5;
				break;
			case rule_set_pixelism:
				c_world2[c][r] = lives ? life <= 3 : life >= 5;
				break;
			case rule_set_amebas:
				c_world2[c][r] = lives ? life >= 4 && life <= 7 : life >= 6;
				break;
			case rule_set_chromosoma1:
				c_world2[c][r] = lives ? life >= 4 && life <= 7 : life >= 7;
				break;
			case rule_set_chromosoma2:
				c_world2[c][r] = lives ? life >= 4 && life <= 7 : life >= 8;
				break;
			case rule_set_chromosoma3:
				c_world2[c][r] = lives ? life >= 4 && life <= 7 : life >= 9;
				break;
			case rule_set_chromosoma4:
				c_world2[c][r] = lives ? life >= 4 && life <= 7 : false;
				break;
			}
		}
	}
	current_world = !current_world;
}
