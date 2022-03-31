#pragma once
#include <vector>
#include <stack>
#include <set>
#include "token.h"
#include "AST_nodes.h"

class AST{

	std::vector<token> tokens;
	std::stack<token> postfix_tokens;
	AST_abstract_node* root_node;

public:

	AST(const std::vector<token>& tokens);
	
	void postfix_form_generate();

	void AST_generation();

	void print();

	void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars);

	std::string generate_cpp_command();
};