#include <vector>
#include <set>
#include <string>
#include <stack>
#include <set>
#include <map>
#include <fstream>
#include <iostream>

class logging {
public:
	virtual void to_log() = 0;

};

class file_logging : logging {
public:

	static void to_log(const std::string& messange, const std::string& file_name = "log.txt");

};

class stream_logging : logging {
public:

	static void to_log(const std::string& messange);

};

enum class compiler_errors_type {
	LEXER,
	PARSER,
	SEMANTIC,
	SYNTAXER,
	CODE_GENERATION
};

class compiler_errors {

public:

	static void error_message(compiler_errors_type error_type, const std::string& message, const std::pair<int, int>& error_coordinate = { -1,-1 });
};

enum class token_type {
	VAR, // Переменная
	VAL, // Константа
	INPUT, // Функция ввода
	PRINT, // Функция вывода
	PLUS, // Плюс
	MINUS, // Минус
	EQUAL, // Равно
	SEMICOLON, // Точка с запятой
	LEFT_B, // Левая скобка
	RIGHT_B, // Правая скобка
	IDENTIFIER, // Имя
	LITERAL, // Литерал
	QUOTE, // Кавычка
	EMPTY
};

class token
{
	std::string lexeme;
	token_type type;
	std::pair<int, int> position;

	static token_type lexeme_to_token(std::string& lexeme);

	static bool is_string(const std::string& lexeme);
	static bool is_int(const std::string& lexeme);
	static bool is_float(const std::string& lexeme);

public:
	token(token_type type = token_type::EMPTY) : type(type) {}
	explicit token(const std::string& lexeme, std::pair<int, int> position = { 0,0 });

	std::vector<std::string> token_inf() const;

	const std::string& get_lexeme() const;
	const token_type& get_type() const;
	const std::pair<int, int>& get_position() const;

};

class lexer {

	std::vector<char> cpm_code;
	std::vector<token> array_of_tokens;
	std::pair<int, int> current_token_in_code;

public:

	lexer(const std::string& file_path);
	void generate_tokens();
	std::vector<token>& get_tokens();
	void print_tokens();
};

class AST_abstract_node
{
protected:
	token data;
	AST_abstract_node* parent;

public:

	AST_abstract_node(const token& data, AST_abstract_node* parent = nullptr) : data(data), parent(parent) {}

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

	void generate_AST(std::stack<token>& tokens, AST_abstract_node* parent);

	~unary_AST_abstract_node();
};

class binary_AST_abstract_node : public AST_abstract_node {
protected:

	AST_abstract_node* left_node, * right_node;

public:
	binary_AST_abstract_node(std::stack<token>& tokens, AST_abstract_node* parent = nullptr);

	void generate_AST(std::stack<token>& tokens, AST_abstract_node* parent);

	~binary_AST_abstract_node();
};

class literal_AST_node : public AST_abstract_node {

public:
	literal_AST_node(const token& data, AST_abstract_node* parent = nullptr) : AST_abstract_node(data, parent) {}

	void print() override;

	void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) override;

	std::string generate_cpp_command() override;
};

class identifier_AST_node : public AST_abstract_node {

public:
	identifier_AST_node(const token& data, AST_abstract_node* parent = nullptr) : AST_abstract_node(data, parent) {}

	void print() override;

	void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) override;

	std::string generate_cpp_command() override;
};

class plus_AST_node : public binary_AST_abstract_node {
public:
	plus_AST_node(std::stack<token>& tokens, AST_abstract_node* parent = nullptr) : binary_AST_abstract_node(tokens, parent) {}

	void print() override;

	void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) override;

	std::string generate_cpp_command() override;
};

class minus_AST_node : public binary_AST_abstract_node {
public:
	minus_AST_node(std::stack<token>& tokens, AST_abstract_node* parent = nullptr) : binary_AST_abstract_node(tokens, parent) {}

	void print() override;

	void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) override;

	std::string generate_cpp_command() override;
};

class input_AST_node : public unary_AST_abstract_node {
public:
	input_AST_node(std::stack<token>& tokens, AST_abstract_node* parent = nullptr) : unary_AST_abstract_node(tokens, parent) {}

	void print() override;

	void semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars) override;

	std::string generate_cpp_command() override;
};

class AST {

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

enum class command_type {
	DECLARATION,
	ASSIGNMENT,
	FUNCTION,
};

class command {
protected:

	token data;

public:
	command(const token& data) : data(data) {}

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

	assignmen_command(const token& data, const std::vector<token>& tokens) : command(data), syntax_tree(tokens) {}

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

class syntaxer {

	std::vector<token> tokens;
	std::vector<command*> commands;

public:

	syntaxer(const std::vector<token>& tokens) : tokens(tokens) {}

	void command_generation();

	void print_commands();

	std::vector<command*>& get_commands();
};

class semanticer
{
	std::vector<command*> commands;
	std::set<std::string> vals, vars;

public:

	semanticer(const std::vector<command*>& commands) : commands(commands) {}

	void semantic_verification();
};

class cpp_generator
{
	std::vector<command*> commands;
	std::ofstream cpp_file;
	std::string cpm_runtime_path;

public:
	cpp_generator(std::vector<command*> commands, const std::string& file_name) : commands(commands), cpp_file(file_name + ".cpp") {}

	void generate_cpp_code();

};

void literal_AST_node::print()
{
	std::cout << '\"' << this->data.get_lexeme() << '\"';
}

void literal_AST_node::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
	return;
}

std::string literal_AST_node::generate_cpp_command()
{
	try
	{
		std::stoll(this->data.get_lexeme());
		return "mixed(" + this->data.get_lexeme() + ")";
	}
	catch (std::exception) 
	{
		try 
		{
			std::stod(this->data.get_lexeme());
			return "mixed(" + this->data.get_lexeme() + ")";
		}
		catch (std::exception)
		{
		}
	}
	std::string temp;
	temp += '"';
	return ("mixed(" + temp + this->data.get_lexeme() + temp + ")");
}

void identifier_AST_node::print()
{
	std::cout << this->data.get_lexeme();
}

void identifier_AST_node::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
	if (vals.find(this->data.get_lexeme()) == vals.end() && vars.find(this->data.get_lexeme()) == vars.end()) 
	{
		compiler_errors::error_message(compiler_errors_type::SYNTAXER, "Uninitialized variable", this->data.get_position());
	}
	return;
}

std::string identifier_AST_node::generate_cpp_command()
{
	return this->data.get_lexeme();
}

void plus_AST_node::print()
{
	std::cout << "("; this->left_node->print(); std::cout << " + "; this->right_node->print(); std::cout << ")";
}

std::string plus_AST_node::generate_cpp_command()
{
	return "(" + this->left_node->generate_cpp_command() + " + " + this->right_node->generate_cpp_command() + ")";
}

void plus_AST_node::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
	this->left_node->semantic_verification(vals, vars);
	this->right_node->semantic_verification(vals, vars);
}

void minus_AST_node::print()
{
	std::cout << "("; this->left_node->print(); std::cout << " - "; this->right_node->print(); std::cout << ")";
}

void minus_AST_node::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
	this->left_node->semantic_verification(vals, vars);
	this->right_node->semantic_verification(vals, vars);
}

std::string minus_AST_node::generate_cpp_command()
{
	return "(" + this->left_node->generate_cpp_command() + " - " + this->right_node->generate_cpp_command() + ")";
}

void input_AST_node::print()
{
	std::cout << "input(";
	if (this->next_node) {
		this->next_node->print();
	}
	std::cout << ")";
}

void input_AST_node::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
	if (this->next_node) {
		this->next_node->semantic_verification(vals, vars);
	}
}

std::string input_AST_node::generate_cpp_command()
{
	if (this->next_node) {
		return "cpm_input(" + this->next_node->generate_cpp_command() + ")";
	}
	return "cpm_input()";
}


void file_logging::to_log(const std::string& messange, const std::string& file_name) {

	std::ofstream file_log(file_name);
	file_log << time << ": " << file_name << '\n';

}

void stream_logging::to_log(const std::string& messange) {

	std::cout << time << ": " << messange << '\n';

}

void compiler_errors::error_message(compiler_errors_type error_type, const std::string& message, const std::pair<int, int>& error_coordinate)
{
	std::string error_information;

	switch (error_type)
	{
	case compiler_errors_type::LEXER: {
		error_information = "Lexical error: ";
	}
	case compiler_errors_type::PARSER: {
		error_information = "Syntax error: ";
	}
	case compiler_errors_type::SEMANTIC: {
		error_information = "Semantic error: ";
	}
	case compiler_errors_type::CODE_GENERATION: {
		error_information = "Generation error: ";
	}
	default:
		error_information = "Unknown error: ";
	}

	error_information += message + "!" + '\n';
	if (error_coordinate.first != -1) {
		error_information += "Line: " + std::to_string(error_coordinate.first) + ", Position : " + std::to_string(error_coordinate.second);
	}

	throw(error_information);
}

token::token(const std::string& lexeme, std::pair<int, int> position) {

	this->position = position;
	std::string temp_lexeme = lexeme;
	type = lexeme_to_token(temp_lexeme);
	this->lexeme = temp_lexeme;
}

token_type token::lexeme_to_token(std::string& lexeme)
{
	if (lexeme == "var") {
		return token_type::VAR;
	}
	if (lexeme == "val") {
		return token_type::VAL;
	}
	if (lexeme == "input") {
		return token_type::INPUT;
	}
	if (lexeme == "print") {
		return token_type::PRINT;
	}
	if (lexeme == "+") {
		return token_type::PLUS;
	}
	if (lexeme == "-") {
		return token_type::MINUS;
	}
	if (lexeme == "=") {
		return token_type::EQUAL;
	}
	if (lexeme == ";") {
		return token_type::SEMICOLON;
	}
	if (lexeme == "(") {
		return token_type::LEFT_B;
	}
	if (lexeme == ")") {
		return token_type::RIGHT_B;
	}
	if (lexeme == "\"") {
		return token_type::QUOTE;
	}
	if (is_int(lexeme) || is_float(lexeme)) {
		return token_type::LITERAL;
	}
	if (is_string(lexeme)) {
		lexeme = lexeme.substr(1, lexeme.size() - 2);
		return token_type::LITERAL;
	}
	return token_type::IDENTIFIER;
}

bool token::is_string(const std::string& lexeme)
{
	if (lexeme.front() == '"' && lexeme.back() == '"') {

		return true;
	}
	return false;
}

bool token::is_int(const std::string& lexeme)
{
	for (auto& i : lexeme) {
		if (i < '0' || i > '9') {
			return false;
		}
	}
	return true;
}

bool token::is_float(const std::string& lexeme)
{
	bool dot = false;
	for (auto& i : lexeme) {
		if (i == '.') {
			if (dot) {
				return false;
			}
			else {
				dot = true;
			}
		}
		else {
			if (i < '0' || i > '9') {
				return false;
			}
		}
	}
	return true;
}

std::vector<std::string> token::token_inf() const {

	std::vector<std::string> inf(3);

	switch (type) {

	case token_type::EQUAL: inf[0] = "EQUAL"; break;
	case token_type::IDENTIFIER: inf[0] = "IDENTIFIER"; break;
	case token_type::PLUS: inf[0] = "PLUS"; break;
	case token_type::INPUT: inf[0] = "INPUT"; break;
	case token_type::LEFT_B: inf[0] = "LEFT_B"; break;
	case token_type::RIGHT_B: inf[0] = "RIGHT_B"; break;
	case token_type::LITERAL: inf[0] = "LITERAL"; break;
	case token_type::MINUS: inf[0] = "MINUS"; break;
	case token_type::VAR: inf[0] = "VAR"; break;
	case token_type::VAL: inf[0] = "VAL"; break;
	case token_type::PRINT: inf[0] = "PRINT"; break;
	case token_type::SEMICOLON: inf[0] = "SEMICOLON"; break;
	case token_type::QUOTE: inf[0] = "QUOTE"; break;

	default:
		inf[0] = "ERROR";
	}

	inf[1] = lexeme;
	inf[2] = '(' + std::to_string(position.first) + ", " + std::to_string(position.second) + ')';
	return inf;
}

const std::string& token::get_lexeme() const {
	return lexeme;
}

const token_type& token::get_type() const {
	return type;
}

const std::pair<int, int>& token::get_position() const {
	return position;
}

lexer::lexer(const std::string& file_path) {


	std::ifstream row_code(file_path, std::ios::binary);
	current_token_in_code = { 1,1 };

	if (!row_code.is_open()) {
		compiler_errors::error_message(compiler_errors_type::LEXER, "could not open the file");
	}

	char temp_ch;
	while (row_code.get(temp_ch)) {
		cpm_code.push_back(temp_ch);
	}
	row_code.close();

}

void lexer::generate_tokens() {

	std::string lexeme;

	bool quotation_open = false;
	for (auto& i : cpm_code) {
		if (quotation_open && i != '"') {
			lexeme += i;
			++current_token_in_code.second;
			continue;
		}
		if (i == '"') {
			if (quotation_open) {
				--current_token_in_code.second;
				lexeme += i;
				array_of_tokens.push_back(token(lexeme, current_token_in_code));
				++current_token_in_code.second;
				lexeme.clear();
				//array_of_tokens.push_back(token(std::string(1,'\"'), current_token_in_code));
				quotation_open = false;
			}
			else {
				if (!lexeme.empty()) {
					--current_token_in_code.second;
					array_of_tokens.push_back(token(lexeme, current_token_in_code));
					++current_token_in_code.second;
				}
				lexeme.clear();
				//array_of_tokens.push_back(token(std::string(1, '\"'), current_token_in_code));
				lexeme += i;
				quotation_open = true;
			}
			++current_token_in_code.second;
			continue;
		}
		if (i == '\n') {
			++current_token_in_code.first;
			current_token_in_code.second = 1;
			continue;
		}
		if (i == '+' || i == '-' || i == '=' || i == ';' || i == '(' || i == ')') {
			if (!lexeme.empty()) {
				--current_token_in_code.second;
				array_of_tokens.push_back(token(lexeme, current_token_in_code));
				++current_token_in_code.second;
			}
			lexeme.clear();
			array_of_tokens.push_back(token(std::string(1, i), current_token_in_code));
			++current_token_in_code.second;
			continue;
		}
		if (i == ' ') {
			if (!lexeme.empty()) {
				--current_token_in_code.second;
				array_of_tokens.push_back(token(lexeme, current_token_in_code));
				++current_token_in_code.second;
			}
			lexeme.clear();
			++current_token_in_code.second;
			continue;
		}
		if (i == '\r') {
			continue;
		}
		lexeme += i;
		++current_token_in_code.second;
	}
	if (quotation_open) {
		compiler_errors::error_message(compiler_errors_type::PARSER, "missing closing quotation mark", current_token_in_code);
	}
	if (!lexeme.empty()) {
		--current_token_in_code.second;
		array_of_tokens.push_back(token(lexeme, current_token_in_code));
		lexeme.clear();
	}
}

std::vector<token>& lexer::get_tokens()
{
	return array_of_tokens;
}

void lexer::print_tokens() {

	std::cout << '\t' << "Type" << "          " << "Literal" << "          " << "Coordinates" << '\n';

	for (auto& i : array_of_tokens) {
		std::vector<std::string> inf = i.token_inf();
		std::cout << '\t' << inf[0];
		for (int j = 0; j < 14 - inf[0].size(); ++j) {
			std::cout << ' ';
		}
		std::cout << inf[1];
		for (int j = 0; j < 17 - inf[1].size(); ++j) {
			std::cout << ' ';
		}
		std::cout << inf[2] << '\n';
	}

}

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
		compiler_errors::error_message(compiler_errors_type::SEMANTIC, "multiple initialization", data.get_position());
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

void syntaxer::command_generation() {

	int token_iterator = 0;
	std::vector<token> current_command, temp_command;
	token temp_token;


	while (token_iterator < tokens.size())
	{
		temp_command.clear();
		temp_token = token_type::EMPTY;
		if (tokens[token_iterator].get_type() == token_type::VAL || tokens[token_iterator].get_type() == token_type::VAR)
		{
			bool is_const = tokens[token_iterator].get_type() == token_type::VAL ? true : false;
			if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::IDENTIFIER)
			{
				++token_iterator;
				temp_token = tokens[token_iterator];
				if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::EQUAL)
				{
					token_iterator += 2;
					while (token_iterator < tokens.size() && tokens[token_iterator].get_type() != token_type::SEMICOLON)
					{
						temp_command.push_back(tokens[token_iterator]);
						++token_iterator;
					}
					if (token_iterator < tokens.size())
					{
						if (!temp_command.empty())
						{
							commands.push_back(new declaration_command(temp_token, temp_command, is_const));
							++token_iterator;
						}
						else
						{
							compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
						}
					}
					else
					{
						--token_iterator;
						compiler_errors::error_message(compiler_errors_type::SYNTAXER, "semicolon is required", tokens[token_iterator].get_position());
					}
				}
				else if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::SEMICOLON)
				{
					++token_iterator;
				}
				else
				{
					compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
				}
			}
			else
			{
				compiler_errors::error_message(compiler_errors_type::SYNTAXER, "identifier is required", tokens[token_iterator].get_position());
			}
		}
		else if (tokens[token_iterator].get_type() == token_type::IDENTIFIER)
		{
			if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::EQUAL)
			{
				temp_token = tokens[token_iterator];
				token_iterator += 2;
				while (token_iterator < tokens.size() && tokens[token_iterator].get_type() != token_type::SEMICOLON)
				{
					temp_command.push_back(tokens[token_iterator]);
					++token_iterator;
				}
				if (token_iterator < tokens.size())
				{
					if (!temp_command.empty())
					{
						commands.push_back(new assignmen_command(temp_token, temp_command));
						++token_iterator;
					}
					else
					{
						compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
					}
				}
				else
				{
					--token_iterator;
					compiler_errors::error_message(compiler_errors_type::SYNTAXER, "semicolon is required", tokens[token_iterator].get_position());
				}
			}
			else
			{
				compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
			}
		}
		else if (tokens[token_iterator].get_type() == token_type::INPUT || tokens[token_iterator].get_type() == token_type::PRINT)
		{
			token_type temp = tokens[token_iterator].get_type();
			if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::LEFT_B)
			{
				temp_token = tokens[token_iterator];
				token_iterator += 2;
				while (token_iterator < tokens.size() && tokens[token_iterator].get_type() != token_type::RIGHT_B)
				{
					temp_command.push_back(tokens[token_iterator]);
					++token_iterator;
				}
				if (token_iterator < tokens.size())
				{
					if (temp == token_type::PRINT && temp_command.empty())
					{
						compiler_errors::error_message(compiler_errors_type::SYNTAXER, "expression is required", tokens[token_iterator].get_position());
					}
					if (token_iterator + 1 < tokens.size() && tokens[token_iterator + 1].get_type() == token_type::SEMICOLON)
					{
						commands.push_back(new function_command(temp_token, temp_command));
						token_iterator += 2;
					}
					else
					{
						compiler_errors::error_message(compiler_errors_type::SYNTAXER, "semicolon is required", tokens[token_iterator].get_position());
					}
				}
				else
				{
					--token_iterator;
					compiler_errors::error_message(compiler_errors_type::SYNTAXER, "closing parenthesis is required", tokens[token_iterator].get_position());
				}
			}
			else
			{
				compiler_errors::error_message(compiler_errors_type::SYNTAXER, "function was expected", tokens[token_iterator].get_position());
			}
		}
		else
		{
			compiler_errors::error_message(compiler_errors_type::SEMANTIC, "incorrect expression", tokens[token_iterator].get_position());
		}
	}

}

void syntaxer::print_commands()
{
	for (auto& command : commands)
	{
		command->print(); std::cout << '\n';
	}
}

std::vector<command*>& syntaxer::get_commands()
{
	return this->commands;
}

unary_AST_abstract_node::unary_AST_abstract_node(std::stack<token>& tokens, AST_abstract_node* parent) : AST_abstract_node((!tokens.empty() ? tokens.top() : token(token_type::EMPTY)), parent)
{
	generate_AST(tokens, parent);
}

void unary_AST_abstract_node::generate_AST(std::stack<token>& tokens, AST_abstract_node* parent)
{
	if (tokens.empty()) {
		next_node = nullptr;
		return;
	}
	switch (tokens.top().get_type())
	{
	case token_type::IDENTIFIER:
	{
		this->next_node = new identifier_AST_node(tokens.top(), this);
		tokens.pop();
		break;
	}
	case token_type::LITERAL:
	{
		this->next_node = new literal_AST_node(tokens.top(), this);
		tokens.pop();
		break;
	}
	case token_type::MINUS:
	{
		if (tokens.size() == 1) {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "incorrect expression", tokens.top().get_position());
		}
		tokens.pop();
		this->next_node = new minus_AST_node(tokens, this);
		break;
	}
	case token_type::PLUS:
	{
		if (tokens.size() == 1) {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "incorrect expression", tokens.top().get_position());
		}
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

binary_AST_abstract_node::binary_AST_abstract_node(std::stack<token>& tokens, AST_abstract_node* parent) : AST_abstract_node(tokens.top(), parent)
{
	this->generate_AST(tokens, parent);
}

void binary_AST_abstract_node::generate_AST(std::stack<token>& tokens, AST_abstract_node* parent)
{
	switch (tokens.top().get_type())
	{
	case token_type::IDENTIFIER:
	{
		this->right_node = new identifier_AST_node(tokens.top(), this);
		tokens.pop();
		break;
	}
	case token_type::LITERAL:
	{
		this->right_node = new literal_AST_node(tokens.top(), this);
		tokens.pop();
		break;
	}
	case token_type::MINUS:
	{
		tokens.pop();
		if (tokens.size() == 1) {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "incorrect expression", tokens.top().get_position());
		}
		this->right_node = new minus_AST_node(tokens, this);
		break;
	}
	case token_type::PLUS:
	{
		tokens.pop();
		if (tokens.size() == 1) {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "incorrect expression", tokens.top().get_position());
		}
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
		this->left_node = new identifier_AST_node(tokens.top(), this);
		tokens.pop();
		break;
	}
	case token_type::LITERAL:
	{
		this->left_node = new literal_AST_node(tokens.top(), this);
		tokens.pop();
		break;
	}
	case token_type::MINUS:
	{
		tokens.pop();
		if (tokens.size() == 1) {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "incorrect expression", tokens.top().get_position());
		}
		this->left_node = new minus_AST_node(tokens, this);
		break;
	}
	case token_type::PLUS:
	{
		tokens.pop();
		if (tokens.size() == 1) {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "incorrect expression", tokens.top().get_position());
		}
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

AST_abstract_node* AST_abstract_node::get_parent()
{
	return parent;
}

void semanticer::semantic_verification()
{
	for (auto& command : commands)
	{
		command->semantic_verification(this->vals, this->vars);
	}
}

void cpp_generator::generate_cpp_code()
{
	cpp_file << "#include " << '\"' << "cpm_runtime.cpp" << '\"' << '\n';
	cpp_file << "int main()" << '\n' << "{" << '\n';
	for (auto& command : commands)
	{
		cpp_file << '\t' << command->generate_cpp_command() << ";" << '\n';
	}
	cpp_file << "}";
	cpp_file.close();
}

AST::AST(const std::vector<token>& tokens) : tokens(tokens)
{	
	this->postfix_form_generate();
	this->AST_generation();
}

std::map<std::pair<token_type, token_type>, int> transitions = {
	{std::make_pair(token_type::IDENTIFIER, token_type::LEFT_B), 1},
	{std::make_pair(token_type::IDENTIFIER, token_type::INPUT), 5},
	{std::make_pair(token_type::IDENTIFIER, token_type::PLUS), 1},
	{std::make_pair(token_type::IDENTIFIER, token_type::MINUS), 1},
	{std::make_pair(token_type::IDENTIFIER, token_type::EMPTY), 1},

	{std::make_pair(token_type::LITERAL, token_type::LEFT_B), 1},
	{std::make_pair(token_type::LITERAL, token_type::INPUT), 5},
	{std::make_pair(token_type::LITERAL, token_type::PLUS), 1},
	{std::make_pair(token_type::LITERAL, token_type::MINUS), 1},
	{std::make_pair(token_type::LITERAL, token_type::EMPTY), 1},

	{std::make_pair(token_type::LEFT_B, token_type::LEFT_B), 2},
	{std::make_pair(token_type::LEFT_B, token_type::INPUT), 2},
	{std::make_pair(token_type::LEFT_B, token_type::PLUS), 2},
	{std::make_pair(token_type::LEFT_B, token_type::MINUS), 2},
	{std::make_pair(token_type::LEFT_B, token_type::EMPTY), 2},

	{std::make_pair(token_type::RIGHT_B, token_type::LEFT_B), 4},
	{std::make_pair(token_type::RIGHT_B, token_type::INPUT), 5},
	{std::make_pair(token_type::RIGHT_B, token_type::PLUS), 4},
	{std::make_pair(token_type::RIGHT_B, token_type::MINUS), 4},
	{std::make_pair(token_type::RIGHT_B, token_type::EMPTY), 7},

	{std::make_pair(token_type::INPUT, token_type::LEFT_B), 2},
	{std::make_pair(token_type::INPUT, token_type::INPUT), 5},
	{std::make_pair(token_type::INPUT, token_type::PLUS), 2},
	{std::make_pair(token_type::INPUT, token_type::MINUS), 2},
	{std::make_pair(token_type::INPUT, token_type::EMPTY), 2},

	{std::make_pair(token_type::PLUS, token_type::LEFT_B), 2},
	{std::make_pair(token_type::PLUS, token_type::INPUT), 5},
	{std::make_pair(token_type::PLUS, token_type::PLUS), 3},
	{std::make_pair(token_type::PLUS, token_type::MINUS), 3},
	{std::make_pair(token_type::PLUS, token_type::EMPTY), 2},

	{std::make_pair(token_type::MINUS, token_type::LEFT_B), 2},
	{std::make_pair(token_type::MINUS, token_type::INPUT), 5},
	{std::make_pair(token_type::MINUS, token_type::PLUS), 3},
	{std::make_pair(token_type::MINUS, token_type::MINUS), 3},
	{std::make_pair(token_type::MINUS, token_type::EMPTY), 2},

	{std::make_pair(token_type::EMPTY, token_type::LEFT_B), 6},
	{std::make_pair(token_type::EMPTY, token_type::INPUT), 5},
	{std::make_pair(token_type::EMPTY, token_type::PLUS), 3},
	{std::make_pair(token_type::EMPTY, token_type::MINUS), 3},
	{std::make_pair(token_type::EMPTY, token_type::EMPTY), 3}

};

void AST::postfix_form_generate()
{
	std::stack<token> buffer_stack;

	buffer_stack.push(token(token_type::EMPTY));
	int token_iterator = 0;

	while (token_iterator < tokens.size()) {
		switch (transitions[std::make_pair(tokens[token_iterator].get_type(), buffer_stack.top().get_type())])
		{
		case 1: {
			postfix_tokens.push(tokens[token_iterator]);
			++token_iterator;
			continue;
		}
		case 2: {
			buffer_stack.push(tokens[token_iterator]);
			++token_iterator;
			continue;
		}
		case 3: {
			postfix_tokens.push(buffer_stack.top());
			buffer_stack.pop();
			continue;
		}
		case 4: {
			while (!buffer_stack.empty() && buffer_stack.top().get_type() != token_type::LEFT_B) {
				postfix_tokens.push(buffer_stack.top());
				buffer_stack.pop();
			}
			if (buffer_stack.top().get_type() == token_type::LEFT_B) {
				buffer_stack.pop();
				if (!buffer_stack.empty() && buffer_stack.top().get_type() == token_type::INPUT) {
					postfix_tokens.push(buffer_stack.top());
					buffer_stack.pop();
				}
				++token_iterator;
			}
			continue;
		}
		case 5: {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "opening parenthesis is required", tokens[token_iterator].get_position());
		}
		case 6: {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "closing parenthesis is required", tokens[token_iterator].get_position());
		}
		case 7: {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "extra closing parenthesis", tokens[token_iterator].get_position());
		}
		default:
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "unknown character", tokens[token_iterator].get_position());
		}
	}
	while (buffer_stack.top().get_type() != token_type::EMPTY)
	{
		if (buffer_stack.top().get_type() == token_type::MINUS || buffer_stack.top().get_type() == token_type::PLUS) 
		{
			postfix_tokens.push(buffer_stack.top());
			buffer_stack.pop();
		}
		else if (buffer_stack.top().get_type() == token_type::INPUT) 
		{
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "opening parenthesis is required", tokens[token_iterator - 1].get_position());
		}
		else if (buffer_stack.top().get_type() == token_type::LEFT_B)
		{
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "closing parenthesis is required", tokens[token_iterator - 1].get_position());
		}
		else {
			compiler_errors::error_message(compiler_errors_type::SYNTAXER, "unknown character", tokens[token_iterator - 1].get_position());
		}
	}
}

void AST::AST_generation()
{
	if (postfix_tokens.empty()) {
		this->root_node = nullptr;
	}
	switch (postfix_tokens.top().get_type())
	{
	case token_type::IDENTIFIER:
	{
		this->root_node = new identifier_AST_node(this->postfix_tokens.top());
		this->postfix_tokens.pop();
		break;
	}
	case token_type::LITERAL:
	{
		this->root_node = new literal_AST_node(this->postfix_tokens.top());
		postfix_tokens.pop();
		break;
	}
	case token_type::MINUS:
	{
		postfix_tokens.pop();
		this->root_node = new minus_AST_node(this->postfix_tokens);
		break;
	}
	case token_type::PLUS:
	{
		postfix_tokens.pop();
		this->root_node = new plus_AST_node(this->postfix_tokens);
		break;
	}
	case token_type::INPUT:
	{
		postfix_tokens.pop();
		this->root_node = new input_AST_node(this->postfix_tokens);
		break;
	}
	default:
		compiler_errors::error_message(compiler_errors_type::SYNTAXER, "unknow symbol", postfix_tokens.top().get_position());
	}
	if (!postfix_tokens.empty()) {
		compiler_errors::error_message(compiler_errors_type::SYNTAXER, "incorrect expression", postfix_tokens.top().get_position());
	}
}

void AST::print()
{
	if (this->root_node) {
		this->root_node->print();
	}
}

void AST::semantic_verification(std::set<std::string>& vals, std::set<std::string>& vars)
{
	if (this->root_node) {
		this->root_node->semantic_verification(vals, vars);
	}
}

std::string AST::generate_cpp_command() 
{
	if (this->root_node) {
		return this->root_node->generate_cpp_command();
	}
	return "";
}




int main(int argc, char* argv[]) {
	try {
		std::string file_path = argv[1];

		lexer Lexer(file_path);
		Lexer.generate_tokens();

		syntaxer Syntaxer(Lexer.get_tokens());
		Syntaxer.command_generation();

		semanticer Semanticer(Syntaxer.get_commands());
		Semanticer.semantic_verification();

       while (file_path[file_path.size() - 1] != '.')
		{
			file_path.resize(file_path.size() - 1);
		}
        file_path.resize(file_path.size() - 1);

        std::string file_name = argv[0];
		while (file_name[file_name.size() - 1] != '\\')
		{
			file_name.resize(file_name.size() - 1);
		}
        std::string name;
        while (file_path[file_path.size() - 1] != '\\')
		{
			name = file_path[file_path.size() - 1] + name;
            file_path.resize(file_path.size() - 1);
		}
        file_name += name;
		char _name_[file_name.size()];
		for (int i = 0;i<file_name.size();++i){
			_name_[i] = file_name[i];
		}
		cpp_generator Cpp_generator(Syntaxer.get_commands(), file_name);
		Cpp_generator.generate_cpp_code();
		system(("g++ -o " + name + " " + name + ".cpp & code.exe").c_str());
		system(("del " + name + ".cpp").c_str());
	}
	catch (const std::string error_information) {

		//file_logging::to_log(error_information);
		stream_logging::to_log(error_information);

	}
}