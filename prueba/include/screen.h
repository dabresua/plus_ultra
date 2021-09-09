#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include <stdint.h>
#include <SDL2/SDL.h>

/**
 * @file: sreen.h
 * @brief: Abstract for screens. Provides basic methods for run, paint and
 *         event handling
 */

class Screen {
public:
	/**
	 * @brief: Constructor
	 * @param id  Screen identifier number
	 */
	inline Screen(uint8_t id) {
		this->id = id;
	}

	/**
	 * @brief: Runs the screen actions modifiying its internal state
	 */
	virtual void run() = 0;

	/**
	 * @brief: Paints the screen contents
	 * @param gRenderer SDL rendering state object
	 */
	virtual void paint(SDL_Renderer *gRenderer) = 0;

	/**
	 * @brief: Feeds the screen with any event (keyboard, mouse, touch, ...)
	 * @param event The event handler
	 */
	virtual void event(SDL_Event *event) = 0;

	/**
	 * @brief: Gets the screen identifier
	 * @returns: Screen id
	 */
	inline uint8_t getID() {
		return id;
	}
private:
	uint8_t id; /**< Screen identifier */
};

#endif /* SCREEN_H_INCLUDED */
