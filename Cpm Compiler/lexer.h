#pragma once
#include <vector>
#include <fstream>
#include "token.h"


class lexer{

	std::vector<char> cpm_code;
	std::vector<token> array_of_tokens;
	std::pair<int, int> current_token_in_code;

public:

	lexer(){}
	void generate_lexer(const std::string& file_path);
	void generate_tokens();
	void print_tokens();
};