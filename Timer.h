#pragma once
#include <SDL2/SDL.h>
#include "Logging.h"
#include <SDL2/SDL_image.h>

namespace angelogames {
	class Timer
	{
	public:
		//Initializes variables
		Timer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

	private:
		//The clock time when the timer started
		Uint32 m_StartTicks;

		//The ticks stored when the timer was paused
		Uint32 m_PausedTicks;

		//The timer status
		bool m_Paused;
		bool m_Started;

	};
}
