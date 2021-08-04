#ifndef GOL_H_INCLUDED
#define GOL_H_INCLUDED

#include <string>
#include <coordinates.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define PIXEL_SIZE (1)

typedef enum rule_set_t {
	rule_set_classic = 0,
	rule_set_laberinth1,
	rule_set_laberinth2,
	rule_set_laberinth3,
	rule_set_forest,
	rule_set_grow_quick,
	rule_set_grow_front1,
	rule_set_strange_blood,
	rule_set_grow_front2,
	rule_set_static_psico1,
	rule_set_static_psico2,
	rule_set_static_rorschach,
	rule_set_static_gotele,
	rule_set_amongus,
	rule_set_pixelism,
	rule_set_amebas,
	rule_set_chromosoma1,
	rule_set_chromosoma2,
	rule_set_chromosoma3,
	rule_set_chromosoma4,
} rule_set_t;

typedef enum screen_t {
	screen_init,
	screen_gol
} screen_t;

class Gol {
public:
	Gol(unsigned int w, unsigned int h, rule_set_t r);
	std::string to_string();
	std::string to_hex();
	void generate(int life);
	void run();
	void paint_screen(SDL_Renderer* gRenderer);
	void gc();

	inline int getW()
	{
		return width;
	}

	inline int getH()
	{
		return height;
	}

	inline void set(Coordinates c)
	{
		set_or_clr(c, true);
	}

	inline void clr(Coordinates c)
	{
		set_or_clr(c, false);
	}

	inline screen_t getScreen()
	{
		return screen;
	}

private:
	unsigned int width, height;
	rule_set_t rule_set;
	bool **world1, **world2;
	bool current_world;
	screen_t screen;
	void set_or_clr(Coordinates c, bool set);
	void inc_life(bool **c_world, unsigned int c, unsigned int r,
	              unsigned int *life);
	void paint_screen_init(SDL_Renderer* gRenderer);
	void paint_screen_gol(SDL_Renderer* gRenderer);
};

#endif /* GOL_H_INCLUDED */
