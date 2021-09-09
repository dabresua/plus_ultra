#ifndef G2D_ENGINE_H_INCLUDED
#define G2D_ENGINE_H_INCLUDED

/**
 * @file g2d_engine.h
 * @brief Basic engine for two threads
 *        The main engine runs and paints screens. Is slow because runs a lot
 *        of processing
 *        The secondary engine saves and notifies events. Is a lot quicker and
 *        blocks the main engine
 *        a blocking thread
 */

#include <g2d_screen.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <stdio.h>

class g2d_engine_t {
public:
	/**
	 * @brief empty constructor
	 */
	g2d_engine_t();

	/**
	 * @brief graphic constructor
	 * @param r 2D renderer
	 */
	g2d_engine_t(SDL_Renderer *r);

	/**
	 * @brief sets the engine in idle status
	 */
	void g2d_engine_start();

	/**
	 * @brief Adds a new screen to the engine
	 * @param scr The screen to add
	 */
	void g2d_engine_screen_push(g2d_screen_t *scr);

	 /**
	  * @brief Indicates if the engine must be runned
	  * @returns true if is ready to run, false otherwise
	  */
	bool g2d_engine_torun();

	/**
	 * @brief Runs the engine
	 */
	void g2d_engine_run();

	/**
	 * @brief Indicates if the event engine must be runned
	 * @returns true if is ready to run, false otherwise
	 */
   bool g2d_engine_ev_torun();

   /**
	* @brief Runs the event engine
	*/
   void g2d_engine_ev_run();

	/**
	 * @brief Notifies an event to the engine
	 * @remarks The event will be notified to the screens when the main engine
	 *          isn't running. If not, is save into a stack and is notified
	 *          after main engine finishes
	 */
	void g2d_engine_event_notify(SDL_Event *ev);

	/**
	 * @brief Sets the refresh time of the engine
	 * @param hz Desired refresh frecuency
	 */
	void g2d_refresh_set(uint8_t hz);

	/**
	 * @brief Gets the amount of time[ms] that the thread can sleep
	 * @returns time in milliseconds
	 */
	inline
	uint16_t g2d_sleep_period_get()
	{
		return this->notifiying?1:this->sleep_period;
	}

	/**
	 * @brief Gets the amount of time[ms] that the thread can sleep
	 * @returns time in milliseconds
	 */
	inline
	uint16_t g2d_ev_sleep_period_get()
	{
		return this->ev_sleep;
	}

	/**
	 * @brief Updates the amount of time[ms] that the thread can sleep
	 * @remark Call this before @ref g2d_sleep_period_get if
	 *         @ref g2d_engine_torun hasn't been called in a while
	 */
	void g2d_sleep_period_update();
private:
	/* ---- Navigation ---- */
	std::vector <g2d_screen_t*> scr_list; /**< List of screens */
	uint8_t                   scr_active; /**< Active screen */

	/* ---- Graphics ---- */
	SDL_Renderer *rend; /**< Graphics renderer */

	/* ---- engine speed ---- */
	bool         running:1; /**< Semaphore */
	uint16_t     en_period; /**< Period between runs */
	int16_t       en_sleep; /**< For thread sleep */
	std::chrono::time_point<std::chrono::system_clock> en_start; /**< start time */
	std::chrono::time_point<std::chrono::system_clock> en_end;   /**< end time */

	/* ---- Events ---- */
	bool       notifiying:1; /* Semaphore */
	std::queue <SDL_Event> ev_stack; /**< FIFO of events */
	uint16_t    ev_period; /**< Period between runs */
	int16_t      ev_sleep; /**< For thread sleep */
	std::chrono::time_point<std::chrono::system_clock> ev_start; /**< start time */
	std::chrono::time_point<std::chrono::system_clock> ev_end;   /**< end time */
};

#endif /* G2D_ENGINE_H_INCLUDED */
