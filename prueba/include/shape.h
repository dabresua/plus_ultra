#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

/**
 * @file shape.h
 * @brief Represents a geometric 2D shape
 */

#include <assert.h>

typedef enum shape_type_t {
	shape_type_point,
	shape_type_rect,
	shape_type_square,
	shape_type_circle,
} shape_type_t;

class Shape {
public:
	/**
	 * @brief Empty constructor
	 */
	Shape() {
		this->type = shape_type_point;
	}

	/**
	 * @brief Constructor
	 * @param type The type of the shape
	 * @param a magnitude for the selected type
	 */
	Shape(shape_type_t type, uint16_t a) {
		this->type = type;
		if (type == shape_type_square) {
			this->side = a;
		} else if (type == shape_type_circle) {
			this->radius = a;
		} else {
			assert(false);
		}
	}

	/**
	 * @brief Constructor
	 * @param type The type of the shape
	 * @param a magnitude for the selected type
	 * @param b magnitude for the selected type
	 */
	Shape(shape_type_t type, uint16_t a, uint16_t b) {
		this->type = type;
		if (type == shape_type_rect) {
			this->sides[0] = a;
			this->sides[1] = b;
		} else {
			assert(false);
		}
	}

	/**
	 * @brief Checks if a coordinate is inside the shape
	 * @param x x coordinate
	 * @param y y coordinate
	 * @returns true if the event is inside the button, false otherwise
	 */
	 bool is_inside(int32_t x, int32_t y) {
		 if (x < 0 || y < 0)
		 	return false;
		switch (this->type) {
		case shape_type_rect:
			if (x > this->sides[0] || y > this->sides[1])
				return false;
			return true;
		case shape_type_square:
			if (x > this->side || y > this->side)
				return false;
			return true;
		case shape_type_circle:
			/* TODO */
			return false;
		case shape_type_point:
		default: return false;
		}
		assert(false);
	 }

	 /**
 	 * @brief: Paints the shape
 	 * @param gRenderer SDL rendering state object
	 * @param x x coordinate
	 * @param y y coordinate
 	 */
 	void paint(SDL_Renderer *gRenderer, uint16_t x, uint16_t y, SDL_Texture *t) {
		SDL_Rect body;
 		switch (this->type) {
 		case shape_type_rect:
			body.x = x;
			body.y = y;
			body.w = this->sides[0];
			body.h = this->sides[1];
			SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
			SDL_RenderFillRect( gRenderer, &body );
			SDL_RenderCopy(gRenderer, t, NULL, &body);
			break;
		case shape_type_square:
			body.x = x;
			body.y = y;
			body.w = this->side;
			body.h = this->side;
			SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
			SDL_RenderFillRect( gRenderer, &body );
			SDL_RenderCopy(gRenderer, t, NULL, &body);
			break;
		case shape_type_circle:
			/* TODO */
		case shape_type_point:
			/* TODO */
		default:
			assert(false);
 		}
 	}

private:
	shape_type_t type; /**< The type of the shape */
	union {
		uint16_t side;
		uint16_t sides[2];
		uint16_t radius;
	};
};

#endif /* SHAPE_H_INCLUDED */
