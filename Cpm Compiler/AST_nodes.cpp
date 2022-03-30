#include "AST_nodes.h"
#include <iostream>

mixed literal_AST_node::code_generation()
{
	return mixed(this->lexeme);
}

void literal_AST_node::print()
{
	std::cout << '\"' << this->lexeme << '\"';
}

mixed identifier_AST_node::code_generation()
{
    return mixed(); //------------ Написать хранение переменных
}

void identifier_AST_node::print()
{
	std::cout << this->identifier;
}

mixed plus_AST_node::code_generation()
{
	return left_node->code_generation() + right_node->code_generation();
}

void plus_AST_node::print()
{
	std::cout << "("; this->left_node->print(); std::cout << " + "; this->right_node->print(); std::cout << ")";
}

mixed minus_AST_node::code_generation()
{
	return left_node->code_generation() - right_node->code_generation();
}

void minus_AST_node::print()
{
	std::cout << "("; this->left_node->print(); std::cout << " + "; this->right_node->print(); std::cout << ")";
}

mixed input_AST_node::code_generation()
{
	std::cout << next_node->code_generation();
	mixed temp;
	std::cin >> temp;
	return temp;
}

void input_AST_node::print()
{
	std::cout << "input("; this->next_node->print(); std::cout << ")";
}
