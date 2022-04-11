#pragma once
#include "lexer.h"
#include <fstream>
#include "compiler_errors.h"
#include <iostream>

lexer::lexer(const std::string & file_path){
	// Лишние пустые строки.

	// А зачем читать файл как бинарный? Проще считать в строку
	// и уже по ней пробегаться в цикле.
	std::ifstream row_code(file_path, std::ios::binary);
	current_token_in_code = { 1,1 };

	if (!row_code.is_open()) {
		compiler_errors::error_message(compiler_errors_type::LEXER, "could not open the file");
	}
		
	char temp_ch;
	while (row_code.get(temp_ch)) {
		cpm_code.push_back(temp_ch);
	}
	row_code.close();
	// Лишняя пустая строка.
}

void lexer::generate_tokens() {
	// Лишняя пустая строка.
	std::string lexeme;

	bool quotation_open = false;
	int  temp_c = 0;
	for (auto& i : cpm_code) {
		// Магические числа, лучше использовать enum чтобы код был читаемей.
		if (temp_c == 2)
		{
			if (i == '\n')
			{
				if (!lexeme.empty()) {
					array_of_tokens.push_back(token(lexeme, current_token_in_code)); // Clang-Tidy: Use emplace_back instead of push_back
				}
				lexeme.clear();
				++current_token_in_code.first;
				current_token_in_code.second = 1;
				temp_c = 0;
				continue;
			}
			else 
			{
				continue;
			}
		} 
		else if (temp_c == 1)
		{
			if (i == '/')
			{
				temp_c = 2;
				continue;
			}
			else
			{
				lexeme = '/' + lexeme;
				temp_c = 0;
			}
		}
		else
		{
			if (i == '/')
			{
				temp_c = 1;
				continue;
			}
			else
			{
				temp_c = 0;
			}
		}
		if (quotation_open && i != '"') {
			lexeme += i;
			++current_token_in_code.second;
			continue;
		}
		if (i == '"') {
			if (quotation_open) {
				--current_token_in_code.second;
				lexeme += i;
				array_of_tokens.push_back(token(lexeme, current_token_in_code));
				++current_token_in_code.second;
				lexeme.clear();
				//array_of_tokens.push_back(token(std::string(1,'\"'), current_token_in_code));
				quotation_open = false;
			}
			else {
				if (!lexeme.empty()) {
					--current_token_in_code.second;
					array_of_tokens.push_back(token(lexeme, current_token_in_code));
					++current_token_in_code.second;
				}
				lexeme.clear();
				//array_of_tokens.push_back(token(std::string(1, '\"'), current_token_in_code));
				lexeme += i;
				quotation_open = true;
			}
			++current_token_in_code.second;
			continue;
		}
		if (i == '\n') {
			// Проблема со стилем кода, здесь фигурная скобка на новой строке, в других местах на той же!
			if (temp_c == 1) // Unreachable code
			{
				// Этот код недостижим.
				lexeme = '/' + lexeme;
				temp_c = 0;
			}
			++current_token_in_code.first;
			current_token_in_code.second = 1;
			continue;
		}
		if (i == '+' || i == '-' || i == '=' || i == ';' || i == '(' || i == ')') {
			if (!lexeme.empty()) {
				--current_token_in_code.second;
				array_of_tokens.push_back(token(lexeme, current_token_in_code));
				++current_token_in_code.second;
			}
			lexeme.clear();
			array_of_tokens.push_back(token(std::string(1, i), current_token_in_code));
			++current_token_in_code.second;
			continue;
		}
		if (i == ' ') {
			if (!lexeme.empty()) {
				--current_token_in_code.second;
				array_of_tokens.push_back(token(lexeme, current_token_in_code));
				++current_token_in_code.second;
			}
			lexeme.clear();
			++current_token_in_code.second;
			continue;
		}
		if (i == '\r') {
			continue;
		}
		lexeme += i;
		++current_token_in_code.second;
	}
	if (quotation_open) {
		compiler_errors::error_message(compiler_errors_type::PARSER, "missing closing quotation mark", current_token_in_code);
	}
	if (!lexeme.empty()) {
		--current_token_in_code.second;
		array_of_tokens.push_back(token(lexeme, current_token_in_code));
		lexeme.clear();
	}
}

// Проблема со стилем кода, здесь фигурная скобка на новой строке, в других местах на той же!
std::vector<token>& lexer::get_tokens()
{
	return array_of_tokens;
}

void lexer::print_tokens(){

	std::cout << '\t' << "Type" << "          " << "Literal" << "          " << "Coordinates" << '\n';

	for (auto& i : array_of_tokens) {
		std::vector<std::string> inf = i.token_inf();
		std::cout << '\t' << inf[0];
		for (int j = 0; j < 14 - inf[0].size(); ++j) {
			std::cout << ' ';
		}
		std::cout << inf[1];
		for (int j = 0; j < 17 - inf[1].size(); ++j) {
			std::cout << ' ';
		}
		std::cout << inf[2] << '\n';
	}

}

