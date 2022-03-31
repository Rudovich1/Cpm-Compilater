#pragma once
#include <string>
#include <set>
#include "token.hpp"
#include "AST_abstract_nodes.hpp"
#include "compiler_errors.hpp"

class literal_AST_node : public AST_abstract_node {

public:
	literal_AST_node(const token& data, AST_abstract_node* parent = nullptr);

	void print() override;

	void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) override;

	std::string generate_cpp_command() override;
};

class identifier_AST_node : public AST_abstract_node {

public:
	identifier_AST_node(const token& data, AST_abstract_node* parent = nullptr);

	void print() override;

	void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) override;

	std::string generate_cpp_command() override;
};

class plus_AST_node : public binary_AST_abstract_node {
public:
	plus_AST_node(std::stack<token>& tokens, AST_abstract_node* parent = nullptr);

	void print() override;

	void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) override;

	std::string generate_cpp_command() override;
};

class minus_AST_node : public binary_AST_abstract_node {
public:
	minus_AST_node(std::stack<token>& tokens, AST_abstract_node* parent = nullptr);

	void print() override;

	void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) override;

	std::string generate_cpp_command() override;
};

class input_AST_node : public unary_AST_abstract_node {
public:
	input_AST_node(std::stack<token>& tokens, AST_abstract_node* parent = nullptr);

	void print() override;

	void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) override;

	std::string generate_cpp_command() override;
};
