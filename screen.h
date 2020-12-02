#pragma once
#include <SDL2/SDL.h>
#include "Logging.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <array>
#include "Dot.h"
#include "Pacman.h"
#include "Maze.h"

namespace angelogames {
	class Screen
	{
	public:
		SDL_Window* m_window; //The window we'll be rendering to
		SDL_Renderer* m_renderer; //The window renderer

	private:
		std::unique_ptr<Logging> log;
		const int m_kScreenWidth = 224;
		const int m_kScreenHeight = 288;
		//const static int m_kBoardWidth = 600;
		//const static int m_kBoardHeight = 600;

		std::unique_ptr<Dot> m_dot;
		std::unique_ptr<Pacman> m_pacman;
		std::unique_ptr<Maze> m_maze;

		//Current animation frame
		int m_frame;
		const int m_kAnimationDelayFrames = 8;

		
	//////////////
	/// METHODS

	public:
		Screen();
		virtual ~Screen();
		void EventHandler(SDL_Event& event);
		void RenderObjects();
		void MoveObjects();
		void UpdateScreen();
		void Close();

	private:
		void LoadGameTextures();
		SDL_Texture* LoadSingleTexture(std::string path);
		void ClearScreen();
	};
}