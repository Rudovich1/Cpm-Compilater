#pragma once

#include <vector>
#include "token.h"
#include "commands.h"

// Классы должны писаться в CamelCase.
// Лучше было назвать класс Parser.
class syntaxer {
   // Лишняя пустая строка.
	std::vector<token> tokens;
	std::vector<command*> commands;

public:
   // Лишняя пустая строка.
	syntaxer(const std::vector<token>& tokens) : tokens(tokens){}

	void command_generation();

	void print_commands();

	std::vector<command*>& get_commands();
};

