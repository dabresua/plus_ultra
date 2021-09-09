#include <screen_opening.h>
#include <iostream>

Screen_opening::Screen_opening(uint8_t id) : Screen(id)
{
	this->buttons_shape = Shape(shape_type_rect, 100, 20);
	this->buttons[0] = Button(100, 100, &this->buttons_shape, "Play");
	this->buttons[1] = Button(500, 200, &this->buttons_shape, "Quit");
	this->option_selected = screen_opening_option_none;
}

void Screen_opening::run()
{
	/* Do nothing: just events */
}

void Screen_opening::paint(SDL_Renderer *gRenderer)
{
	for (uint8_t i = 0; i < 2; i++) {
		this->buttons[i].paint(gRenderer);
	}
}

void Screen_opening::event(SDL_Event *event)
{
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		std::cout << "Mouse on " << event->button.x << ", " << event->button.y << std::endl;
		for (uint8_t i = 0; i < 2; i++) {
			if (this->buttons[i].is_inside(event->button.x, event->button.y)) {
				std::cout << "Mouse on button " << (int)i << std::endl;
				this->option_selected = (screen_opening_option_t)(i+1);
			}
		}
	}
}
