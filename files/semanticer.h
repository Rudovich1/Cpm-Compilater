#pragma once

#include "commands.h"
#include <string>

class semanticer
{
	std::vector<command*> commands;
	std::set<std::string> vals, vars;

public:

	semanticer(const std::vector<command*>& commands) : commands(commands){}

	void semantic_verification();
};

