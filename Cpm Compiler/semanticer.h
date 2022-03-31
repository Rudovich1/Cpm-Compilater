#pragma once
#include <vector>
#include <set>
#include <string>
#include "commands.h"

class semanticer
{
	std::vector<command*> commands;
	std::set<std::string> vals, vars;

public:

	semanticer(const std::vector<command*>& commands) : commands(commands){}

	void semantic_verification();
};

