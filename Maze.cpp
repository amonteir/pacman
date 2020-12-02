#include "Maze.h"

namespace angelogames 
{

	Maze::Maze() 
	{
		//Initialises the log file
		log = std::make_unique <Logging>("maze.log");

		//Initialises the maze with Wall id
		for (auto& rows : m_maze)
			for (auto& column : rows)
				column = "W";


	}

	Maze::~Maze() 
	{
		log->close();
	}

	void Maze::LoadTextures(SDL_Renderer* renderer)
	{



	}
}