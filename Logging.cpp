#include "Logging.h"

namespace angelogames {

	Logging::Logging(std::string filename) {

		this->filename = filename;
		log_file.open(this->filename);

		std::string msg = this->filename + " log file initiated.";
		write(msg);

	}

	Logging::~Logging() {}

	void Logging::close() {

		std::string msg = this->filename + " log file closed.";
		write(msg);
		log_file.close();

	}


	void Logging::write(std::string msg) {

		auto time_now = std::chrono::system_clock::now();
		char str[35];
		std::time_t time_now_formatted = std::chrono::system_clock::to_time_t(time_now);
		ctime_s(str, sizeof str, &time_now_formatted);
		log_file << str << "\t" << msg << std::endl;

	}

}