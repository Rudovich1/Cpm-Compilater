#pragma once

#include <string>
#include "token.h"
#include "compiler_errors.h"
#include "log.h"
#include "AST.h"

enum class command_type {
	DECLARATION,
	ASSIGNMENT,
	FUNCTION,
};

class command {
protected:

	std::string identifier;   
	virtual void code_generation() = 0; // переделать 

public:
	command(const std::string& identifier) : identifier(identifier){}

	std::string get_identifier();

	virtual void print() = 0;

};

class declaration_command : public command {

	bool is_const;

public:
	declaration_command(bool is_const, const std::string& identifier) : is_const(is_const), command(identifier) {}

	void code_generation() override; // ---

	void print() override;
};

class assignmen_command : public command {

	bool is_const;
	AST syntax_tree;

public:
	assignmen_command(bool is_const, const std::string& identifier, const std::vector<token>& tokens) : is_const(is_const), command(identifier), syntax_tree(tokens){}

	void code_generation() override; //---

	void print() override;
};

class function_command : public command {

	AST syntax_tree;

public:
	function_command(const std::string& identifier, const std::vector<token>& tokens) : syntax_tree(tokens), command(identifier) {}

	void code_generation() override; //---

	void print() override;
};
