#pragma once
#include "AST_abstract_nodes.h"
#include <string>


class literal_AST_node : public AST_abstract_node {
	std::string lexeme;

public:
	literal_AST_node(const std::string& lexeme, AST_abstract_node* parent = nullptr) : AST_abstract_node(parent), lexeme(lexeme){}

	mixed code_generation() override;

	void print() override;
};

class identifier_AST_node : public AST_abstract_node {
	std::string identifier;

public:
	identifier_AST_node(const std::string& identifier, AST_abstract_node* parent = nullptr) : AST_abstract_node(parent), identifier(identifier){}

	mixed code_generation() override;

	void print() override;
};

class plus_AST_node : public binary_AST_abstract_node {
public:
	plus_AST_node(std::stack<token>& tokens, AST_abstract_node* parent = nullptr) : binary_AST_abstract_node(tokens, parent){}

	mixed code_generation() override;

	void print() override;
};

class minus_AST_node : public binary_AST_abstract_node {
public:
	minus_AST_node(std::stack<token>& tokens, AST_abstract_node* parent = nullptr) : binary_AST_abstract_node(tokens, parent) {}

	mixed code_generation() override;

	void print() override;
};

class input_AST_node : public unary_AST_abstract_node {
public:
	input_AST_node(std::stack<token>& tokens, AST_abstract_node* parent = nullptr) : unary_AST_abstract_node(tokens, parent){}

	mixed code_generation() override;

	void print() override;
};
