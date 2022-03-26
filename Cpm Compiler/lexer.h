#pragma once
#include "token.h"
#include <vector>
#include <fstream>

class lexer
{
	std::string file_path;
	std::vector<char> cpm_code;
	std::vector<token> array_of_tokens;

	std::vector<token> ::iterator current_token;
	std::pair<int, int> current_token_in_code;

	std::string separate_symbols = { ' ', '\n', ';', '(', ')', '=', '+', '-', '"', '\r'};

public:

	explicit lexer(const std::string& file_path);

	void generate_tokens();

	void print_tokens();
};