#pragma once

#include <string>
#include "compiler_errors.h"
#include "log.h"

enum class command_type {
	DECLARATION,
	ASSIGNMENT,
	FUNCTION,
};

class command {
protected:

	virtual std::string code_generation() = 0;

};

class declaration_command : protected command {

	bool is_const;
	std::string lexeme;

	declaration_command(bool is_const, const std::string lexeme) : is_const(is_const), lexeme(lexeme){}

	std::string code_generation() override;

};

class assignmen_command : protected command {



};

