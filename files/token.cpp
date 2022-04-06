#pragma once
#include "token.h"

token::token(const std::string& lexeme, std::pair<int, int> position){ 
	
	this->position = position;
	std::string temp_lexeme = lexeme;
	type = lexeme_to_token(temp_lexeme);
	this->lexeme = temp_lexeme;
}

token_type token::lexeme_to_token(std::string& lexeme)
{
	if (lexeme == "var") {
		return token_type::VAR;
	}
	if (lexeme == "val") {
		return token_type::VAL;
	}
	if (lexeme == "input") {
		return token_type::INPUT;
	}
	if (lexeme == "print") {
		return token_type::PRINT;
	}
	if (lexeme == "+") {
		return token_type::PLUS;
	}
	if (lexeme == "-") {
		return token_type::MINUS;
	}
	if (lexeme == "=") {
		return token_type::EQUAL;
	}
	if (lexeme == ";") {
		return token_type::SEMICOLON;
	}
	if (lexeme == "(") {
		return token_type::LEFT_B;
	}
	if (lexeme == ")") {
		return token_type::RIGHT_B;
	}
	if (lexeme == "\"") {
		return token_type::QUOTE;
	}
	if (is_int(lexeme) || is_float(lexeme)) {
		return token_type::LITERAL;
	}
	if (is_string(lexeme)) {
		lexeme = lexeme.substr(1, lexeme.size() - 2);
		return token_type::LITERAL;
	}
	return token_type::IDENTIFIER;
}

bool token::is_string(const std::string& lexeme)
{
	if (lexeme.front() == '"' && lexeme.back() == '"') {
		
		return true;
	}
	return false;
}

bool token::is_int(const std::string& lexeme)
{
	for (auto& i : lexeme) {
		if (i < '0' || i > '9') {
			return false;
		}
	}
	return true;
}

bool token::is_float(const std::string& lexeme)
{
	bool dot = false;
	for (auto& i : lexeme) {
		if (i == '.') {
			if (dot) {
				return false;
			}
			else {
				dot = true;
			}
		}
		else {
			if (i < '0' || i > '9') {
				return false;
			}
		}
	}
	return true;
}

std::vector<std::string> token::token_inf() const{

	std::vector<std::string> inf(3);

	switch (type){

	case token_type::EQUAL: inf[0] = "EQUAL"; break;
		case token_type::IDENTIFIER: inf[0] = "IDENTIFIER"; break;
		case token_type::PLUS: inf[0] = "PLUS"; break;
		case token_type::INPUT: inf[0] = "INPUT"; break;
		case token_type::LEFT_B: inf[0] = "LEFT_B"; break;
		case token_type::RIGHT_B: inf[0] = "RIGHT_B"; break;
		case token_type::LITERAL: inf[0] = "LITERAL"; break;
		case token_type::MINUS: inf[0] = "MINUS"; break;
		case token_type::VAR: inf[0] = "VAR"; break;
		case token_type::VAL: inf[0] = "VAL"; break;
		case token_type::PRINT: inf[0] = "PRINT"; break;
		case token_type::SEMICOLON: inf[0] = "SEMICOLON"; break;
		case token_type::QUOTE: inf[0] = "QUOTE"; break;
	
	default:
		inf[0] = "ERROR";
	}

	inf[1] = lexeme;
	inf[2] = '(' + std::to_string(position.first) + ", " + std::to_string(position.second) + ')';
	return inf;
}

const std::string& token::get_lexeme() const{
	return lexeme;
}

const token_type& token::get_type() const{
	return type;
}

const std::pair<int, int>& token::get_position() const{
	return position;
}
