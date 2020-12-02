#pragma once
#include <vector>
#include <iostream>
#include "Logging.h"
#include <array>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


namespace angelogames {
	class Maze
	{

	private:
		//Pointer to the log
		std::unique_ptr<Logging> log;

		//Dimensions of the maze
		static const int m_kMazeWidth = 224;
		static const int m_kMazeHeight = 288;

		//Matrix that holds the maze data
		std::array<std::array<std::string, m_kMazeWidth>, m_kMazeHeight> m_maze;

		//Tile flavours
		const enum class m_eTileType {None, Wall, Count};
		//Array with all possible textures for the maze tiles, referenced to the m_eTileType enum
		std::array<SDL_Texture, (int)m_eTileType::Count> m_tile_textures;

		
		

	public:
		Maze();
		virtual ~Maze();
		std::string GetTileValue(int row, int col){ return m_maze[row][col]; }
		
	private:
		void LoadTextures(SDL_Renderer* renderer);
	};
}
