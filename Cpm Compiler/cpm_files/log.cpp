#pragma once
#include "log.h"
#include <fstream>
#include <iostream>

void file_logging::to_log(const std::string& messange, const std::string& file_name){

	std::ofstream file_log(file_name);
	file_log << time << ": " << file_name << '\n';

}

void stream_logging::to_log(const std::string& messange){

	std::cout << time << ": " << messange << '\n';

}


