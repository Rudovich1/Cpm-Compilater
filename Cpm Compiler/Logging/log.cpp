#include <iostream>
#include <fstream>
#include "Cpm_headers\log.hpp"

void file_logging::to_log(const std::string& messange, const std::string& file_name){

	std::ofstream file_log(file_name);
	file_log << time << ": " << file_name << '\n';

}

void stream_logging::to_log(const std::string& messange){

	std::cout << time << ": " << messange << '\n';

}


