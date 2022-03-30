#include "AST_abstract_nodes.h"
#include "AST_nodes.h"
#include "mixed.h"
#include "compiler_errors.h"

unary_AST_abstract_node::unary_AST_abstract_node(std::stack<token>& tokens, AST_abstract_node* parent) : AST_abstract_node(parent)
{
	switch (tokens.top().get_type())
	{
	case token_type::IDENTIFIER:
	{
		this->next_node = new identifier_AST_node(tokens.top().get_lexeme(), this);
		tokens.pop();
		break;
	}
	case token_type::LITERAL:
	{
		this->next_node = new literal_AST_node(tokens.top().get_lexeme(), this);
		tokens.pop();
		break;
	}
	case token_type::MINUS:
	{
		tokens.pop();
		this->next_node = new minus_AST_node(tokens, this);
		break;
	}
	case token_type::PLUS:
	{
		tokens.pop();
		this->next_node = new plus_AST_node(tokens, this);
		break;
	}
	case token_type::INPUT:
	{
		tokens.pop();
		this->next_node = new input_AST_node(tokens, this);
		break;
	}
	default:
		compiler_errors::error_message(compiler_errors_type::SYNTAXER, "unknow symbol", tokens.top().get_position());
	}
}

unary_AST_abstract_node::~unary_AST_abstract_node()
{
	delete(next_node);
}

binary_AST_abstract_node::binary_AST_abstract_node(std::stack<token>& tokens, AST_abstract_node* parent)
{
	switch (tokens.top().get_type())
	{
	case token_type::IDENTIFIER:
	{
		this->right_node = new identifier_AST_node(tokens.top().get_lexeme(), this);
		tokens.pop();
		break;
	}
	case token_type::LITERAL:
	{
		this->right_node = new literal_AST_node(tokens.top().get_lexeme(), this);
		tokens.pop();
		break;
	}
	case token_type::MINUS:
	{
		tokens.pop();
		this->right_node = new minus_AST_node(tokens, this);
		break;
	}
	case token_type::PLUS:
	{
		tokens.pop();
		this->right_node = new plus_AST_node(tokens, this);
		break;
	}
	case token_type::INPUT:
	{
		tokens.pop();
		this->right_node = new input_AST_node(tokens, this);
		break;
	}
	default:
		compiler_errors::error_message(compiler_errors_type::SYNTAXER, "unknow symbol", tokens.top().get_position());
	}

	switch (tokens.top().get_type())
	{
	case token_type::IDENTIFIER:
	{
		this->left_node = new identifier_AST_node(tokens.top().get_lexeme(), this);
		tokens.pop();
		break;
	}
	case token_type::LITERAL:
	{
		this->left_node = new literal_AST_node(tokens.top().get_lexeme(), this);
		tokens.pop();
		break;
	}
	case token_type::MINUS:
	{
		tokens.pop();
		this->left_node = new minus_AST_node(tokens, this);
		break;
	}
	case token_type::PLUS:
	{
		tokens.pop();
		this->left_node = new plus_AST_node(tokens, this);
		break;
	}
	case token_type::INPUT:
	{
		tokens.pop();
		this->left_node = new input_AST_node(tokens, this);
		break;
	}
	default:
		compiler_errors::error_message(compiler_errors_type::SYNTAXER, "unknow symbol", tokens.top().get_position());
	}
}

binary_AST_abstract_node::~binary_AST_abstract_node()
{
	delete(left_node);
	delete(right_node);
}

AST_abstract_node::AST_abstract_node(AST_abstract_node* parent) : parent(parent) {}

AST_abstract_node* AST_abstract_node::get_parent()
{
	return parent;
}
