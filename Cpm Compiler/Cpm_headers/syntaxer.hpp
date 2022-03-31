#pragma once

#include <set>
#include <string>
#include "token.hpp"
#include "commands.hpp"

class syntaxer {

	std::vector<token> tokens;
	std::vector<command*> commands;

public:

	syntaxer(const std::vector<token>& tokens) : tokens(tokens){}

	void command_generation();

	void print_commands();

	std::vector<command*>& get_commands();
};

