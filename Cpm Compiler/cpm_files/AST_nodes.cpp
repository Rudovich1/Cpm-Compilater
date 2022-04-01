#pragma once
#include "AST_nodes.h"
#include <iostream>
#include "compiler_errors.h"

void literal_AST_node::print()
{
	std::cout << '\"' << this->data.get_lexeme() << '\"';
}

void literal_AST_node::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
	return;
}

std::string literal_AST_node::generate_cpp_command()
{
	try
	{
		std::stoll(this->data.get_lexeme());
		return "mixed(" + this->data.get_lexeme() + ")";
	}
	catch (std::exception) 
	{
		try 
		{
			std::stod(this->data.get_lexeme());
			return "mixed(" + this->data.get_lexeme() + ")";
		}
		catch (std::exception)
		{
		}
	}
	std::string temp;
	temp += '"';
	return ("mixed(" + temp + this->data.get_lexeme() + temp + ")");
}

void identifier_AST_node::print()
{
	std::cout << this->data.get_lexeme();
}

void identifier_AST_node::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
	if (vals.find(this->data.get_lexeme()) == vals.end() && vars.find(this->data.get_lexeme()) == vars.end()) 
	{
		compiler_errors::error_message(compiler_errors_type::SYNTAXER, "Uninitialized variable", this->data.get_position());
	}
	return;
}

std::string identifier_AST_node::generate_cpp_command()
{
	return this->data.get_lexeme();
}

void plus_AST_node::print()
{
	std::cout << "("; this->left_node->print(); std::cout << " + "; this->right_node->print(); std::cout << ")";
}

std::string plus_AST_node::generate_cpp_command()
{
	return "(" + this->left_node->generate_cpp_command() + " + " + this->right_node->generate_cpp_command() + ")";
}

void plus_AST_node::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
	this->left_node->semantic_verification(vals, vars);
	this->right_node->semantic_verification(vals, vars);
}

void minus_AST_node::print()
{
	std::cout << "("; this->left_node->print(); std::cout << " - "; this->right_node->print(); std::cout << ")";
}

void minus_AST_node::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
	this->left_node->semantic_verification(vals, vars);
	this->right_node->semantic_verification(vals, vars);
}

std::string minus_AST_node::generate_cpp_command()
{
	return "(" + this->left_node->generate_cpp_command() + " - " + this->right_node->generate_cpp_command() + ")";
}

void input_AST_node::print()
{
	std::cout << "input(";
	if (this->next_node) {
		this->next_node->print();
	}
	std::cout << ")";
}

void input_AST_node::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
	if (this->next_node) {
		this->next_node->semantic_verification(vals, vars);
	}
}

std::string input_AST_node::generate_cpp_command()
{
	if (this->next_node) {
		return "cpm_input(" + this->next_node->generate_cpp_command() + ")";
	}
	return "cpm_input()";
}
