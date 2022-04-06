#pragma once

#include "token.h"
#include <string>
#include <set>
#include "AST.h"

enum class command_type {
	DECLARATION,
	ASSIGNMENT,
	FUNCTION,
};

class command {
protected:

	token data;

public:
	command(const token& data) : data(data){}

	std::string get_identifier();

	virtual void print() = 0;

	virtual void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) = 0;

	virtual std::string generate_cpp_command() = 0;

};

class declaration_command : public command {
public:

	bool is_const;
	AST syntax_tree;

	declaration_command(const token& data, const std::vector<token>& tokens, bool is_const) : command(data), is_const(is_const), syntax_tree(tokens) {}

	void print() override;

	void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) override;

	std::string generate_cpp_command() override;
};

class assignmen_command : public command {

	AST syntax_tree;

public:

	assignmen_command(const token& data, const std::vector<token>& tokens) : command(data), syntax_tree(tokens){}

	void print() override;

	void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) override;

	std::string generate_cpp_command() override;
};

class function_command : public command {

	AST syntax_tree;

public:
	function_command(const token& data, const std::vector<token>& tokens) : syntax_tree(tokens), command(data) {}

	void print() override;

	void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) override;

	std::string generate_cpp_command() override;
};
