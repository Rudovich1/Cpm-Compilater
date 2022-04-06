#pragma once

#include "commands.h"
#include "fstream"

class cpp_generator
{
	std::vector<command*> commands;
	std::ofstream cpp_file;
	std::string cpm_runtime_path;

public:
	cpp_generator(std::vector<command*> commands, const std::string& file_name) : commands(commands), cpp_file(file_name + ".cpp") {}

	void generate_cpp_code();

};

