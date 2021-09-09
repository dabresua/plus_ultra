#include <g2d_engine.h>

/* ----- Private API ----- */
#define G2D_ENGINE_SCREEN_MAX (100) /**< Max number of screens */

/* ----- Public API ----- */
g2d_engine_t::g2d_engine_t()
{
	this->scr_active = 0;

	this->en_period = 1;
	this->en_sleep = 1000;

	this->st = g2d_engine_st_init;
}

g2d_engine_t::g2d_engine_t(SDL_Renderer *r) : g2d_engine_t
{
	this->rend = r;
}

void g2d_engine_t::g2d_engine_start()
{
	/* TODO: check there are screens */
	this->st = g2d_engine_st_init;
}

void g2d_engine_t::g2d_engine_screen_push(g2d_screen_t *scr)
{
	if (this->scr_list.size() >= G2D_ENGINE_SCREEN_MAX)
		return;

	this->scr_list.push_back(scr);
}

void g2d_engine_t::g2d_sleep_period_update()
{
	this->en_start = std::chrono::system_clock::now();
	this->en_end = this->en_start;
	this->en_sleep = this->en_period;
}

bool g2d_engine_t::g2d_engine_torun()
{
	if (this->en_sleep <= 0 && !this->notifiying) {
		if (this->scr_list[this->scr_active].g2d_screen_torun() ||
		    this->scr_list[this->scr_active].g2d_screen_topaint()) {
			return true;
		} else {
			g2d_sleep_period_update();
			return false;
		}
	}
}

void g2d_engine_t::g2d_ev_sleep_period_update()
{
	this->ev_start = std::chrono::system_clock::now();
	this->ev_end = this->ev_start;
	this->ev_sleep = this->ev_period;
}

bool g2d_engine_t::g2d_ev_engine_torun()
{
	if (this->ev_sleep <= 0 && !this->running)
		if (!this->ev_stack.empty) {
			return true;
		} else {
			g2d_ev_sleep_period_update();
			return false;
		}
	}
}

void g2d_engine_t::g2d_engine_run()
{
	assert(this->en_sleep <= 0);

	this->running = true;
	this->en_start = std::chrono::system_clock::now();
	if (this->scr_list[this->scr_active].g2d_screen_torun()) {
		this->scr_list[this->scr_active].g2d_screen_run();
	}
	if (this->scr_list[this->scr_active].g2d_screen_topaint()) {
		this->scr_list[this->scr_active].g2d_screen_paint(this->rend);
	}
	this->en_end = std::chrono::system_clock::now();
	int elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>
	                 (this->en_end - this->en_start).count();
	this->en_sleep = static_cast<uint16_t>(this->en_period - elapsed_ms);
	this->running = false;
}

void g2d_engine_t::g2d_ev_engine_run()
{
	assert(this->ev_period <= 0 && !this->running);

	this->notifiying = true;
	this->ev_start = std::chrono::system_clock::now();
	while (!this->ev_stack.empty) {
		SDL_Event ev = this->ev_stack.pop();
		this->scr_list[this->scr_active].g2d_screen_notify(ev);
	}
	this->ev_end = std::chrono::system_clock::now();
	int elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>
					 (this->ev_end - this->ev_start).count();
	this->ev_sleep = static_cast<uint16_t>(this->ev_period - elapsed_ms);
	this->notifiying = false;
}

void g2d_engine_t::g2d_engine_event_notify(SDL_Event *ev)
{
	/* TODO: max number of events */
	if (this->running || this->notifiying) {
		this->ev_stack.push(*ev);
	} else {
		this->notifiying = true;
		this->scr_list[this->scr_active].g2d_screen_notify(&ev);
		this->notifiying = false;
	}
}
