#pragma once
#include <iostream>
#include <fstream> // used for log file
#include <chrono> // used for log file
#include <ctime> // used for log file
#include <algorithm>

namespace angelogames {
	class Logging
	{
	private:
		std::ofstream log_file;
		std::string filename;

	public:
		//const enum class LOGS {Screen, Game, Computer, Board, Player, Main};

	public:
		Logging(std::string filename);
		virtual ~Logging();
		void close();
		void write(std::string msg);

	};

}

