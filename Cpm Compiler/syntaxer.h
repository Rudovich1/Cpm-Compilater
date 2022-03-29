#pragma once

#include <set>
#include <string>
#include "cpm_compiler.h"
#include "token.h"
#include "commands.h"

class syntaxer {

	std::set<std::string> vars, vals;
	std::vector<token> tokens;
	std::vector<command*> commands;

public:

	syntaxer(const std::vector<token>& tokens) : tokens(tokens){}

	void command_generation();

	bool is_exist_val(const std::string& lexeme);
	bool is_exist_var(const std::string& lexeme);



};

