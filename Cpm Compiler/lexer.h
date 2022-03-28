#pragma once
#include "token.h"
#include <vector>
#include <fstream>

class lexer
{
	static std::string file_path;
	static std::vector<char> cpm_code;
	static std::vector<token> array_of_tokens;

	static std::vector<token> ::iterator current_token;
	static std::pair<int, int> current_token_in_code;


public:

	static void generate_tokens();

	static void generate_lexer(const std::string& file_path);

	static void print_tokens();
};