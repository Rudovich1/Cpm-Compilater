#pragma once

#include <set>
#include <string>
#include "cpm_compiler.h"

class syntaxer {

	std::set<std::string> vars, vals;

public:

	bool is_exist_val(const std::string& lexeme);
	bool is_exist_var(const std::string& lexeme);

};

