#pragma once
#include <vector>
#include "token.h"
#include <stack>
#include "AST_abstract_nodes.h"
#include <string>
#include <set>

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