#pragma once

#include <set>
#include <string>
#include "cpm_compiler.h"
#include "token.h"
#include "commands.h"

class syntaxer {

	std::vector<token> tokens;
	std::vector<command*> commands;

public:

	syntaxer(const std::vector<token>& tokens) : tokens(tokens){}

	void command_generation();

	void print_commands();

	std::vector<command*>& get_commands();
};

