#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

/**
 * @file: button.h
 * @brief: Implements a button on the screen
 */

#include <shape.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>

class Button {
public:
	/**
	 * @brief Empty constructor
	 */
	Button() {
		this->x = 0;
		this->y = 0;
		this->shape = NULL;
	}

	/**
	 * @brief Constructor
	 * @param x     x coordinate
	 * @param y     y coordinate
	 * @param s     Shape
	 * @param text  button text
	 */
	Button(int x, int y, Shape *s, std::string text) {
		this->x = x;
		this->y = y;
		this->shape = s;
		this->text = text;
		this->font = TTF_OpenFont("FreeMono.ttf", 24);
		assert(this->font != NULL);
	}

	/**
	 * @brief Checks if the event has been generated inside the button area
	 * @param x x coordinate of the event
	 * @param y y coordinate of the event
	 * @returns true if the event is inside the button, false otherwise
	 */
	bool is_inside(uint16_t x, uint16_t y) {
		return this->shape->is_inside((x-this->x), (y-this->y));
	}

	/**
	 * @brief: Paints the button
	 * @param gRenderer SDL rendering state object
	 */
	void paint(SDL_Renderer *gRenderer) {
		SDL_Color c = {0xFF, 0, 0};
		SDL_Surface *s = TTF_RenderText_Solid(this->font, this->text.c_str(), c);
		SDL_Texture *t = SDL_CreateTextureFromSurface(gRenderer, s);
		this->shape->paint(gRenderer, this->x, this->y, t);
	}

private:
	uint16_t x;        /**< x coordinate */
	uint16_t y;        /**< y coordinate */
	Shape *shape;      /**< Shape pointer */
	std::string text;  /**< Button text */
	TTF_Font* font;    /**< Message font */
};

#endif /* BUTTON_H_INCLUDED */
