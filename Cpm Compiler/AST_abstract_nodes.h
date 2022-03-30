#pragma once
#include <stack>
#include "token.h"
#include "mixed.h"

class AST_abstract_node
{
	AST_abstract_node* parent;

public:
	virtual mixed code_generation() = 0;

	AST_abstract_node(AST_abstract_node* parent = nullptr);
	 
	AST_abstract_node* get_parent();

	virtual void print() = 0;
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

