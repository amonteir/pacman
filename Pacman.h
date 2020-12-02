#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Logging.h"
#include <array>
#include <tuple>

namespace angelogames {
	class Pacman
	{
	public:
		//Pacman Sprites Texture
		SDL_Texture* m_pacman;

	private:
		std::unique_ptr<Logging> log;

		const enum class m_eAnimation {Idle, WalkRight, WalkLeft, WalkUp, WalkDown, Count};
		static const int m_AnimationFrames = 2;

		//Array of tuples that store the 3 the pacman sprite clips as w, h, x0, y0, x1, y1, x2, y2 respectively. Coords are used to animate the pacman
		std::array<std::array <SDL_Rect, m_AnimationFrames>, (int)m_eAnimation::Count> m_animation_clips;
		SDL_Rect m_beginning_clip;


		//Maximum axis velocity of the pacman
		static const int m_kVelocity = 1;

		// Pacman image dimensions
		static const int m_pacman_width = 16;
		static const int m_pacman_height = 16;

		//The X and Y offsets of the pacman
		int m_pos_x, m_pos_y;
		//The velocity of the pacman
		int m_vel_x, m_vel_y;
		// direction of movement, takes values from m_eAnimation
		int m_direction;

		/////////////////
		// METHODS
	public:
		//Initializes the variables
		Pacman(SDL_Renderer* renderer);
		// destroys the object, frees memory
		virtual ~Pacman();
		//Takes key presses and adjusts the dot's velocity
		void EventHandler(SDL_Event& e);
		//Moves the dot
		void Move(int screen_width, int screen_height);
		//Renders the dot texture on the screen
		void Render(SDL_Renderer* renderer, int frame, int screen_width, int screen_height, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL);
		// Return the number of animation frames
		int GetAnimationFrames() { return m_AnimationFrames; }

	private:
		void LoadTextures(SDL_Renderer* renderer);


	};
}
