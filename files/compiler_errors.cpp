#pragma once
#include "compiler_errors.h"

void compiler_errors::error_message(compiler_errors_type error_type, const std::string& message, const std::pair<int, int>& error_coordinate)
{
	std::string error_information;

	switch (error_type)
	{
	case compiler_errors_type::LEXER: {
		error_information = "Lexical error: ";
		break;
	}
	case compiler_errors_type::PARSER: {
		error_information = "Syntax error: ";
		break;
	}
	case compiler_errors_type::SEMANTIC: {
		error_information = "Semantic error: ";
		break;
	}
	case compiler_errors_type::CODE_GENERATION: {
		error_information = "Generation error: ";
		break;
	}
	case compiler_errors_type::SYNTAXER: {
		error_information = "Syntax error: ";
		break;
	}
	default:
		error_information = "Unknown error: ";
		break;
	}

	error_information += message + "!" + '\n';
	if (error_coordinate.first != -1) {
		error_information += "Line: " + std::to_string(error_coordinate.first) + ", Position : " + std::to_string(error_coordinate.second);
	}

   // Плохо кидать не исключение, а строку!
   // Здесь должно быть бросание стандартного исключения
   // в которое передается строка.
   // А вообще лучше сделать сам класс наследником std::exception и кидать его.
   // И сделать метод get_message, который бы делал строку, как выше.
   // Также скобки не нужны для throw.
	throw(error_information);
}