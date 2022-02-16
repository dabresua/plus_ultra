#ifndef GOL_H_INCLUDED
#define GOL_H_INCLUDED

#include <string>
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

class Gol {
	private:
	int width, height;       /**< World size */
	rule_set_t rule_set;     /**< Rule to apply */
	bool **world1, **world2; /**< Pointer to matrix */
	bool current_world;      /**< Current world indicator */

	/**
	 * @brief Set the cell object
	 * 
	 * @param row  row
	 * @param col  column
	 * @param live live status of the cell
	 */
	void set_cell(int row, int col, bool live);

	/**
	 * @brief 
	 * 
	 * @param c_world 
	 * @param c 
	 * @param r 
	 * @param life 
	 */
	void inc_life(bool **c_world, int c, int r, unsigned int *life);

	/**
	 * @brief Initializes the screen
	 * 
	 * @param gRenderer rendered handler
	 */
	void paint_screen_init(SDL_Renderer* gRenderer);

	/**
	 * @brief Paints the screen with the current world
	 * 
	 * @param gRenderer renderer handler
	 */
	void paint_screen_gol(SDL_Renderer* gRenderer);

public:
	/**
	 * @brief Construct a new Gol object
	 * 
	 * @param w 
	 * @param h 
	 * @param r 
	 */
	Gol(int w, int h, rule_set_t r);

	/**
	 * @brief returns the world in string format
	 * 
	 * @return std::string 
	 */
	std::string to_string();

	/**
	 * @brief returns the world in hexadecimal format
	 * 
	 * @return std::string 
	 */
	std::string to_hex();

	/**
	 * @brief Populates the world randomly
	 * 
	 * @param life percentage of live cells
	 */
	void generate(int life);

	/**
	 * @brief single iteration of the world
	 * 
	 */
	void run();

	/**
	 * @brief Paints the current world in the renderer
	 * 
	 * @param gRenderer renderer handler
	 */
	void paint_screen(SDL_Renderer* gRenderer);

	/**
	 * @brief garbage collector???
	 * 
	 */
	void gc();

	/**
	 * @brief gets the width
	 * 
	 * @return int 
	 */
	inline int getW()
	{
		return width;
	}

	/**
	 * @brief gets the height
	 * 
	 * @return int 
	 */
	inline int getH()
	{
		return height;
	}

	/**
	 * @brief Set the cell object
	 * 
	 * @param row 
	 * @param col 
	 */
	inline void set_cell(int row, int col)
	{
		set_cell(row, col, true);
	}

	/**
	 * @brief 
	 * 
	 * @param row 
	 * @param col 
	 */
	inline void clr_cell(int row, int col)
	{
		set_cell(row, col, false);
	}
};

#endif /* GOL_H_INCLUDED */
