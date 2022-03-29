#include "syntaxer.h"
#include <vector>
#include "compiler_errors.h"
#include "commands.h"
#include "token.h"
#include "AST.h"

bool syntaxer::is_exist_val(const std::string& lexeme)
{
	return vals.find(lexeme) != vals.end();
}

bool syntaxer::is_exist_var(const std::string& lexeme)
{
	return vars.find(lexeme) != vars.end();
}

void syntaxer::command_generation() {

	int token_iterator = 0;
	std::vector<token> current_command, temp_command;
	std::string temp_lexeme;
	

	while (token_iterator < tokens.size()) {
		temp_command.clear();
		temp_lexeme.clear();
		if (tokens[token_iterator].get_type() == token_type::VAL || tokens[token_iterator].get_type() == token_type::VAR) {
			bool is_const = tokens[token_iterator].get_type() == token_type::VAL ? true : false;
			if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::IDENTIFIER) {
				++token_iterator;
				if (is_exist_val(tokens[token_iterator].get_lexeme()) || is_exist_var(tokens[token_iterator].get_lexeme())) {
					compiler_errors::error_message(compiler_errors_type::SYNTAXER, "repeat declaration", tokens[token_iterator].get_position());
				}

				commands.push_back(new declaration_command(is_const, tokens[token_iterator].get_lexeme()));
				
				if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::EQUAL) {
					temp_lexeme = tokens[token_iterator].get_lexeme();
					token_iterator += 2;
					while (token_iterator < tokens.size() && tokens[token_iterator].get_type() != token_type::SEMICOLON) {
						temp_command.push_back(tokens[token_iterator]);
						++token_iterator;
					}
					if (token_iterator < tokens.size()) {
						if (!temp_command.empty()) {
							commands.push_back(new assignmen_command(is_const, temp_lexeme, temp_command));
							++token_iterator;
						}
						else {
							compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
						}
					}
					else {
						--token_iterator;
						compiler_errors::error_message(compiler_errors_type::SYNTAXER, "semicolon is required", tokens[token_iterator].get_position());
					}
				}
				else if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::SEMICOLON) {
					++token_iterator;
				}
				else {
					compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
				}
			}
			else {
				compiler_errors::error_message(compiler_errors_type::SYNTAXER, "identifier is required", tokens[token_iterator].get_position()); 
			}
		}
		else if (tokens[token_iterator].get_type() == token_type::IDENTIFIER) {
			if (is_exist_val(tokens[token_iterator].get_lexeme()) || is_exist_var(tokens[token_iterator].get_lexeme())) {
				if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::EQUAL) {
					if (!is_exist_val(tokens[token_iterator].get_lexeme())) {
						temp_lexeme = tokens[token_iterator].get_lexeme();
						token_iterator += 2;
						while (token_iterator < tokens.size() && tokens[token_iterator].get_type() != token_type::SEMICOLON) {
							temp_command.push_back(tokens[token_iterator]);
							++token_iterator;
						}
						if (token_iterator < tokens.size()) {
							if (!temp_command.empty()) {
								commands.push_back(new assignmen_command(false, temp_lexeme, temp_command));
								++token_iterator;
							}
							else {
								compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
							}
						}
						else {
							--token_iterator;
							compiler_errors::error_message(compiler_errors_type::SYNTAXER, "semicolon is required", tokens[token_iterator].get_position());
						}
					}
					else {
						compiler_errors::error_message(compiler_errors_type::SYNTAXER, "the identifier cannot be changed", tokens[token_iterator].get_position());
					}
				}
				else {
					compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
				}
			}
			else {
				compiler_errors::error_message(compiler_errors_type::SYNTAXER, "unknown identifier", tokens[token_iterator].get_position());
			}
		}
		else if (tokens[token_iterator].get_type() == token_type::INPUT || tokens[token_iterator].get_type() == token_type::PRINT) {
			token_type temp = tokens[token_iterator].get_type();
			if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::LEFT_B) {
				token_iterator += 2;
				while (token_iterator < tokens.size() && tokens[token_iterator].get_type() != token_type::RIGHT_B) {
					temp_command.push_back(tokens[token_iterator]);
					++token_iterator;
				}
				if (token_iterator < tokens.size()) {
					if (temp == token_type::PRINT && temp_command.empty()) {
						compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
					}
					if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::SEMICOLON) {
						commands.push_back(new function_command(temp_lexeme, temp_command));
						token_iterator += 2;
					}
					else {
						compiler_errors::error_message(compiler_errors_type::SYNTAXER, "semicolon is required", tokens[token_iterator].get_position());
					}
				}
				else {
					--token_iterator;
					compiler_errors::error_message(compiler_errors_type::SYNTAXER, "closing parenthesis is required", tokens[token_iterator].get_position());
				}
			}
			else {
				compiler_errors::error_message(compiler_errors_type::SYNTAXER, "function was expected", tokens[token_iterator].get_position());
			}
		}
		else {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "incorrect expression", tokens[token_iterator].get_position());
		}
	}

}