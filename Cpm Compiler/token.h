#pragma once
#include <string>
#include <vector>

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
	QUOTE // Кавычка
};

class token
{
	std::string lexeme;
	token_type type;
	std::pair<int, int> position;

public:
	explicit token(const std::string& lexeme, std::pair<int, int> position = {0,0});

	std::vector<std::string> token_inf();

private:
	static token_type lexeme_to_token(const std::string& lexeme);

	static bool is_string(const std::string& lexeme);
	static bool is_int(const std::string& lexeme);
	static bool is_float(const std::string& lexeme);
};