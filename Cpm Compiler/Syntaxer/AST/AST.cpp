#include <map>
#include "Cpm_headers\token.hpp"
#include "Cpm_headers\compiler_errors.hpp"
#include "Cpm_headers\AST.hpp"

AST::AST(const std::vector<token>& tokens) : tokens(tokens)
{	
	this->postfix_form_generate();
	this->AST_generation();
}

std::map<std::pair<token_type, token_type>, int> transitions = {
	{std::make_pair(token_type::IDENTIFIER, token_type::LEFT_B), 1},
	{std::make_pair(token_type::IDENTIFIER, token_type::INPUT), 5},
	{std::make_pair(token_type::IDENTIFIER, token_type::PLUS), 1},
	{std::make_pair(token_type::IDENTIFIER, token_type::MINUS), 1},
	{std::make_pair(token_type::IDENTIFIER, token_type::EMPTY), 1},

	{std::make_pair(token_type::LITERAL, token_type::LEFT_B), 1},
	{std::make_pair(token_type::LITERAL, token_type::INPUT), 5},
	{std::make_pair(token_type::LITERAL, token_type::PLUS), 1},
	{std::make_pair(token_type::LITERAL, token_type::MINUS), 1},
	{std::make_pair(token_type::LITERAL, token_type::EMPTY), 1},

	{std::make_pair(token_type::LEFT_B, token_type::LEFT_B), 2},
	{std::make_pair(token_type::LEFT_B, token_type::INPUT), 2},
	{std::make_pair(token_type::LEFT_B, token_type::PLUS), 2},
	{std::make_pair(token_type::LEFT_B, token_type::MINUS), 2},
	{std::make_pair(token_type::LEFT_B, token_type::EMPTY), 2},

	{std::make_pair(token_type::RIGHT_B, token_type::LEFT_B), 4},
	{std::make_pair(token_type::RIGHT_B, token_type::INPUT), 5},
	{std::make_pair(token_type::RIGHT_B, token_type::PLUS), 4},
	{std::make_pair(token_type::RIGHT_B, token_type::MINUS), 4},
	{std::make_pair(token_type::RIGHT_B, token_type::EMPTY), 7},

	{std::make_pair(token_type::INPUT, token_type::LEFT_B), 2},
	{std::make_pair(token_type::INPUT, token_type::INPUT), 5},
	{std::make_pair(token_type::INPUT, token_type::PLUS), 2},
	{std::make_pair(token_type::INPUT, token_type::MINUS), 2},
	{std::make_pair(token_type::INPUT, token_type::EMPTY), 2},

	{std::make_pair(token_type::PLUS, token_type::LEFT_B), 2},
	{std::make_pair(token_type::PLUS, token_type::INPUT), 5},
	{std::make_pair(token_type::PLUS, token_type::PLUS), 3},
	{std::make_pair(token_type::PLUS, token_type::MINUS), 3},
	{std::make_pair(token_type::PLUS, token_type::EMPTY), 2},

	{std::make_pair(token_type::MINUS, token_type::LEFT_B), 2},
	{std::make_pair(token_type::MINUS, token_type::INPUT), 5},
	{std::make_pair(token_type::MINUS, token_type::PLUS), 3},
	{std::make_pair(token_type::MINUS, token_type::MINUS), 3},
	{std::make_pair(token_type::MINUS, token_type::EMPTY), 2},

	{std::make_pair(token_type::EMPTY, token_type::LEFT_B), 6},
	{std::make_pair(token_type::EMPTY, token_type::INPUT), 5},
	{std::make_pair(token_type::EMPTY, token_type::PLUS), 3},
	{std::make_pair(token_type::EMPTY, token_type::MINUS), 3},
	{std::make_pair(token_type::EMPTY, token_type::EMPTY), 3}

};

void AST::postfix_form_generate()
{
	std::stack<token> buffer_stack;

	buffer_stack.push(token(token_type::EMPTY));
	int token_iterator = 0;

	while (token_iterator < tokens.size()) {
		switch (transitions[std::make_pair(tokens[token_iterator].get_type(), buffer_stack.top().get_type())])
		{
		case 1: {
			postfix_tokens.push(tokens[token_iterator]);
			++token_iterator;
			continue;
		}
		case 2: {
			buffer_stack.push(tokens[token_iterator]);
			++token_iterator;
			continue;
		}
		case 3: {
			postfix_tokens.push(buffer_stack.top());
			buffer_stack.pop();
			continue;
		}
		case 4: {
			while (!buffer_stack.empty() && buffer_stack.top().get_type() != token_type::LEFT_B) {
				postfix_tokens.push(buffer_stack.top());
				buffer_stack.pop();
			}
			if (buffer_stack.top().get_type() == token_type::LEFT_B) {
				buffer_stack.pop();
				if (!buffer_stack.empty() && buffer_stack.top().get_type() == token_type::INPUT) {
					postfix_tokens.push(buffer_stack.top());
					buffer_stack.pop();
				}
				++token_iterator;
			}
			continue;
		}
		case 5: {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "opening parenthesis is required", tokens[token_iterator].get_position());
		}
		case 6: {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "closing parenthesis is required", tokens[token_iterator].get_position());
		}
		case 7: {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "extra closing parenthesis", tokens[token_iterator].get_position());
		}
		default:
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "unknown character", tokens[token_iterator].get_position());
		}
	}
	while (buffer_stack.top().get_type() != token_type::EMPTY)
	{
		if (buffer_stack.top().get_type() == token_type::MINUS || buffer_stack.top().get_type() == token_type::PLUS) 
		{
			postfix_tokens.push(buffer_stack.top());
			buffer_stack.pop();
		}
		else if (buffer_stack.top().get_type() == token_type::INPUT) 
		{
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "opening parenthesis is required", tokens[token_iterator - 1].get_position());
		}
		else if (buffer_stack.top().get_type() == token_type::LEFT_B)
		{
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "closing parenthesis is required", tokens[token_iterator - 1].get_position());
		}
		else {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "unknown character", tokens[token_iterator - 1].get_position());
		}
	}
}

void AST::AST_generation()
{
	if (postfix_tokens.empty()) {
		this->root_node = nullptr;
	}
	switch (postfix_tokens.top().get_type())
	{
	case token_type::IDENTIFIER:
	{
		this->root_node = new identifier_AST_node(this->postfix_tokens.top());
		this->postfix_tokens.pop();
		break;
	}
	case token_type::LITERAL:
	{
		this->root_node = new literal_AST_node(this->postfix_tokens.top());
		postfix_tokens.pop();
		break;
	}
	case token_type::MINUS:
	{
		postfix_tokens.pop();
		this->root_node = new minus_AST_node(this->postfix_tokens);
		break;
	}
	case token_type::PLUS:
	{
		postfix_tokens.pop();
		this->root_node = new plus_AST_node(this->postfix_tokens);
		break;
	}
	case token_type::INPUT:
	{
		postfix_tokens.pop();
		this->root_node = new input_AST_node(this->postfix_tokens);
		break;
	}
	default:
		compiler_errors::error_message(compiler_errors_type::SYNTAXER, "unknow symbol", postfix_tokens.top().get_position());
	}
	if (!postfix_tokens.empty()) {
		compiler_errors::error_message(compiler_errors_type::SYNTAXER, "incorrect expression", postfix_tokens.top().get_position());
	}
}

void AST::print()
{
	if (this->root_node) {
		this->root_node->print();
	}
}

void AST::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
	if (this->root_node) {
		this->root_node->semantic_verification(vals, vars);
	}
}

std::string AST::generate_cpp_command() 
{
	if (this->root_node) {
		return this->root_node->generate_cpp_command();
	}
	return "";
}
