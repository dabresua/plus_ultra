#ifndef GOL_H_INCLUDED
#define GOL_H_INCLUDED

#include <string>
#include <coordinates.h>
#include <SDL2/SDL.h>

#define PIXEL_SIZE (10)

class Gol {
public:
	Gol(unsigned int w, unsigned int h);
	std::string to_string();
	std::string to_hex();
	void generate(int life);
	void run();
	void paint_screen(SDL_Renderer* gRenderer);

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

private:
	unsigned int width, height;
	bool **world1, **world2;
	bool current_world;
	void set_or_clr(Coordinates c, bool set);
	void inc_life(bool **c_world, unsigned int c, unsigned int r,
	              unsigned int *life);
	void gc();
};

#endif /* GOL_H_INCLUDED */
