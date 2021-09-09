#ifndef SCREEN_OPENING_H_INCLUDED
#define SCREEN_OPENING_H_INCLUDED

/**
 * @file g2d_screen.h
 * @brief Basic screen abstraction for 2d applications
 */

class g2d_screen_t {
public:
/**
 * @brief Empty constructor
 */
g2d_screen_t() {
	this->run = false;
}

/**
 * @brief checks if the screen and its contents should be runned
 */
bool g2d_screen_torun();

/**
 * @brief checks if the screen and its contents should be painted
 */
bool g2d_screen_topaint();

/**
 * @brief runs the screen and its contents
 */
void g2d_screen_run();

/**
 * @brief paints the screen and its contents
 * @param r graphics renderer
 */
void g2d_screen_paint(SDL_renderer *r);

/**
 * @brief notifies the appropiate frame
 * @param ev event
 */
void g2d_screen_notify(SDL_Event ev);
private:
	/* TODO: frame list */
	bool run:1;
};


#endif /* SCREEN_OPENING_H_INCLUDED */
