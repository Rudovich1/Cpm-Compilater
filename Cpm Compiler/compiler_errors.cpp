#include "compiler_errors.h"

void compiler_errors::error_message(compiler_errors_type error_type, const std::string& message, const std::pair<int, int>& error_coordinate)
{
	std::string error_information;

	switch (error_type)
	{
	case compiler_errors_type::LEXER: {
		error_information = "Lexical error: ";
	}
	case compiler_errors_type::PARSER: {
		error_information = "Syntax error: ";
	}
	case compiler_errors_type::SEMANTIC: {
		error_information = "Semantic error: ";
	}
	case compiler_errors_type::CODE_GENERATION: {
		error_information = "Generation error: ";
	}
	default:
		error_information = "Unknown error: ";
	}

	error_information += message + "!'\n'";
	if (error_coordinate.first != -1) {
		error_information += "Line: " + std::to_string(error_coordinate.first) + ", Position : " + std::to_string(error_coordinate.second);
	}

	throw(error_information);
}