
#include <vector>
#include <iostream>
#include "Cpm_headers\compiler_errors.hpp"
#include "Cpm_headers\commands.hpp"
#include "Cpm_headers\token.hpp"
#include "Cpm_headers\AST.hpp"
#include "Cpm_headers\syntaxer.hpp"

void syntaxer::command_generation() {

	int token_iterator = 0;
	std::vector<token> current_command, temp_command;
	token temp_token;
	

	while (token_iterator < tokens.size()) 
	{
		temp_command.clear();
		temp_token = token_type::EMPTY;
		if (tokens[token_iterator].get_type() == token_type::VAL || tokens[token_iterator].get_type() == token_type::VAR) 
		{
			if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::IDENTIFIER) 
			{
				++token_iterator;
				temp_token = tokens[token_iterator];
				commands.push_back(new declaration_command(temp_token));
				if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::EQUAL) 
				{
					token_iterator += 2;
					while (token_iterator < tokens.size() && tokens[token_iterator].get_type() != token_type::SEMICOLON) 
					{
						temp_command.push_back(tokens[token_iterator]);
						++token_iterator;
					}
					if (token_iterator < tokens.size()) 
					{
						if (!temp_command.empty()) 
						{
							commands.push_back(new assignmen_command(temp_token, temp_command));
							++token_iterator;
						}
						else 
						{
							compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
						}
					}
					else 
					{
						--token_iterator;
						compiler_errors::error_message(compiler_errors_type::SYNTAXER, "semicolon is required", tokens[token_iterator].get_position());
					}
				}
				else if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::SEMICOLON) 
				{
					++token_iterator;
				}
				else 
				{
					compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
				}
			}
			else 
			{
				compiler_errors::error_message(compiler_errors_type::SYNTAXER, "identifier is required", tokens[token_iterator].get_position()); 
			}
		}
		else if (tokens[token_iterator].get_type() == token_type::IDENTIFIER) 
		{
			if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::EQUAL) 
			{
				temp_token = tokens[token_iterator];
				token_iterator += 2;
				while (token_iterator < tokens.size() && tokens[token_iterator].get_type() != token_type::SEMICOLON) 
				{
					temp_command.push_back(tokens[token_iterator]);
					++token_iterator;
				}
				if (token_iterator < tokens.size()) 
				{
					if (!temp_command.empty()) 
					{
						commands.push_back(new assignmen_command(temp_token, temp_command));
						++token_iterator;
					}
					else 
					{
						compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
					}
				}
				else 
				{
					--token_iterator;
					compiler_errors::error_message(compiler_errors_type::SYNTAXER, "semicolon is required", tokens[token_iterator].get_position());
				}
			}
			else 
			{
				compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
			}
		}
		else if (tokens[token_iterator].get_type() == token_type::INPUT || tokens[token_iterator].get_type() == token_type::PRINT) 
		{
			token_type temp = tokens[token_iterator].get_type();
			if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::LEFT_B) 
			{
				temp_token = tokens[token_iterator];
				token_iterator += 2;
				while (token_iterator < tokens.size() && tokens[token_iterator].get_type() != token_type::RIGHT_B) 
				{
					temp_command.push_back(tokens[token_iterator]);
					++token_iterator;
				}
				if (token_iterator < tokens.size()) 
				{
					if (temp == token_type::PRINT && temp_command.empty()) 
					{
						compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
					}
					if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::SEMICOLON) 
					{
						commands.push_back(new function_command(temp_token, temp_command));
						token_iterator += 2;
					}
					else 
					{
						compiler_errors::error_message(compiler_errors_type::SYNTAXER, "semicolon is required", tokens[token_iterator].get_position());
					}
				}
				else 
				{
					--token_iterator;
					compiler_errors::error_message(compiler_errors_type::SYNTAXER, "closing parenthesis is required", tokens[token_iterator].get_position());
				}
			}
			else 
			{
				compiler_errors::error_message(compiler_errors_type::SYNTAXER, "function was expected", tokens[token_iterator].get_position());
			}
		}
		else 
		{
			compiler_errors::error_message(compiler_errors_type::SEMANTIC, "incorrect expression", tokens[token_iterator].get_position());
		}
	}

}

void syntaxer::print_commands()
{
	for (auto& command : commands) 
	{
		command->print(); std::cout << '\n';
	}
}

std::vector<command*>& syntaxer::get_commands()
{
	return this->commands;
}
