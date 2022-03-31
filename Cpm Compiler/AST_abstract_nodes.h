#pragma once
#include <stack>
#include <set>
#include "token.h"

class AST_abstract_node
{
protected:
	token data;
	AST_abstract_node* parent;

public:

	AST_abstract_node(const token& data, AST_abstract_node* parent = nullptr) : data(data),  parent(parent){}
	 
	AST_abstract_node* get_parent();

	virtual void print() = 0;

	virtual void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) = 0;

	virtual std::string generate_cpp_command() = 0;
};

class unary_AST_abstract_node : public AST_abstract_node {
protected:

	AST_abstract_node* next_node;

public:
	unary_AST_abstract_node(std::stack<token>& tokens, AST_abstract_node* parent = nullptr);

	~unary_AST_abstract_node();
};

class binary_AST_abstract_node : public AST_abstract_node {
protected:

	AST_abstract_node* left_node, * right_node;

public:
	binary_AST_abstract_node(std::stack<token>& tokens, AST_abstract_node* parent = nullptr);

	~binary_AST_abstract_node();
};

