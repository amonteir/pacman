#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Logging.h"

namespace angelogames {
	class Dot
	{
	public:
		// Dot texture
		SDL_Texture* m_dot_texture;

	private:
		std::unique_ptr<Logging> log;

		//Maximum axis velocity of the dot
		static const int m_kVelocity = 8;

		// Dot image dimensions
		int m_width;
		int m_height;

		//The X and Y offsets of the dot
		int m_pos_x, m_pos_y;
		//The velocity of the dot
		int m_vel_x, m_vel_y;

	/////////////////
	// METHODS
	public:
		//Initializes the variables
		Dot(SDL_Renderer* renderer);
		// destroys the object
		virtual ~Dot();
		void Close();
		//Takes key presses and adjusts the dot's velocity
		void EventHandler(SDL_Event& e);
		//Moves the dot
		void Move(int screen_width, int screen_height);
		//Renders the dot texture on the screen
		void Render(SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL);

	private:
		void LoadTextures(SDL_Renderer* renderer);
		

	};
}
