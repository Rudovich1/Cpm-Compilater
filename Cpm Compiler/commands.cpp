#include "commands.h"

std::string command::get_identifier()
{
    return identifier;
}

void declaration_command::code_generation()
{
}

void declaration_command::print()
{
    if (is_const) {
        std::cout << "val " << this->identifier << ";";
    }
    else {
        std::cout << "var " << this->identifier << ";";
    }
}

void assignmen_command::code_generation()
{
}

void assignmen_command::print()
{
    std::cout << this->identifier << " = "; this->syntax_tree.print(); std::cout << ";";
}

void function_command::code_generation()
{
}

void function_command::print()
{
    std::cout << this->identifier << "("; this->syntax_tree.print(); std::cout << ");";
}
