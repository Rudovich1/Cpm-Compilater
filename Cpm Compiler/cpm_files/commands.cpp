#pragma once
#include "commands.h"
#include <iostream>
#include "compiler_errors.h"

std::string command::get_identifier()
{
    return data.get_lexeme();
}

void declaration_command::print()
{
    if (this->is_const) 
    {
        std::cout << "val " << this->data.get_lexeme() << ";";
    }
    else 
    {
        std::cout << "var " << this->data.get_lexeme() << ";";
    }
}

void declaration_command::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
    if (vals.find(this->data.get_lexeme()) != vals.end() || vars.find(this->data.get_lexeme()) != vars.find(this->data.get_lexeme())) 
    {
        compiler_errors::error_message(compiler_errors_type::SEMANTIC, "multiple initialization",data.get_position());
    }
    this->syntax_tree.semantic_verification(vals, vars);
    if (is_const) 
    {
        vals.insert(this->data.get_lexeme());
    }
    else 
    {
        vars.insert(this->data.get_lexeme());
    }
}

std::string declaration_command::generate_cpp_command()
{
    if (this->is_const) 
    {
        return "const mixed " + this->data.get_lexeme() + " = " + this->syntax_tree.generate_cpp_command();
    }
    return "mixed " + this->data.get_lexeme() + " = " + this->syntax_tree.generate_cpp_command();
}

void assignmen_command::print()
{
    std::cout << this->data.get_lexeme() << " = "; this->syntax_tree.print(); std::cout << ";";
}

void assignmen_command::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
    if (vals.find(this->data.get_lexeme()) != vals.end()) 
    {
        compiler_errors::error_message(compiler_errors_type::SYNTAXER, "changing the constant", this->data.get_position());
    }
    if (vars.find(this->data.get_lexeme()) == vars.end()) 
    {
        compiler_errors::error_message(compiler_errors_type::SYNTAXER, "uninitialized variable", this->data.get_position());
    }
    this->syntax_tree.semantic_verification(vals, vars);
}

std::string assignmen_command::generate_cpp_command()
{
    return this->data.get_lexeme() + " = " + this->syntax_tree.generate_cpp_command();
}

void function_command::print()
{
    std::cout << this->data.get_lexeme() << "("; this->syntax_tree.print(); std::cout << ");";
}

void function_command::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
    this->syntax_tree.semantic_verification(vals, vars);
}

std::string function_command::generate_cpp_command()
{
    if (this->data.get_type() == token_type::INPUT) 
    {
        return "cpm_input(" + this->syntax_tree.generate_cpp_command() + ")";
    }
    return "cpm_print(" + this->syntax_tree.generate_cpp_command() + ")";
}
