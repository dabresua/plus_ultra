#ifndef SCREEN_OPENING_H_INCLUDED
#define SCREEN_OPENING_H_INCLUDED

/**
 * @file: screen_opening.h
 * @brief: The first screen with the main menu
 */

#include <screen.h>
#include <button.h>
#include <shape.h>

class Screen_opening : public Screen {
public:
	/**
	 * @brief Constructor
	 */
	Screen_opening(uint8_t id);

	/**
	 * @brief: Runs the screen actions modifiying its internal state
	 */
	void run();

	/**
	 * @brief: Paints the screen contents
	 * @param gRenderer SDL rendering state object
	 */
	void paint(SDL_Renderer *gRenderer);

	/**
	 * @brief: Feeds the screen with any event (keyboard, mouse, touch, ...)
	 * @param event The event handler
	 */
	void event(SDL_Event *event);
private:
	typedef enum screen_opening_option_t {
		screen_opening_option_none,
		screen_opening_option_play,
		screen_opening_option_quit,
	} screen_opening_option_t;
	screen_opening_option_t option_selected; /**< Selected option */
	Shape buttons_shape;                     /**< Same shape for all buttons */
	Button buttons[2];                       /**< On-screen buttons */
};

#endif /* SCREEN_OPENING_H_INCLUDED */
