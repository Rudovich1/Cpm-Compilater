#pragma once

#include <set>
#include <string>

class syntaxer {

	static std::set<std::string> vals, vars;

public:

	static bool is_exist_val(const std::string& lexeme);
	static bool is_exist_var(const std::string& lexeme);

};

