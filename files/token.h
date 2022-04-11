#pragma once

#include <vector>
#include <string>

// А почему у тебя вдруг файл в CP1251 если другие в UTF-8?
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
	token(token_type type = token_type::EMPTY): type(type){}
	explicit token(const std::string& lexeme, std::pair<int, int> position = {0,0});

	std::vector<std::string> token_inf() const;

	const std::string& get_lexeme() const;
	const token_type& get_type() const;
	const std::pair<int, int>& get_position() const;

};