#include "syntaxer.h"

bool syntaxer::is_exist_val(const std::string& lexeme) {

	return vals.find(lexeme) != vals.end();

}

bool syntaxer::is_exist_var(const std::string& lexeme) {

	return vars.find(lexeme) != vars.end();

}