#pragma once

#include <vector>
#include <string>
#include "token.h"

// Классы должны писаться в CamelCase.
class lexer{
   // А какой смысл хранить код как массив char, если можно просто хранить
   // строку, которая пришла в конструктор?
	std::vector<char> cpm_code;
   // Имя переменной избыточно несет информацию о том, что это массив (хотя это вектор)
   // Достаточно просто tokens.
	std::vector<token> array_of_tokens;
   // Избыточная информация в имени, достаточно current_token.
   // Однако я не сильно понимаю почему текущий токен это пара двух чисел, тут проблема с наименованием!
	std::pair<int, int> current_token_in_code;

public:
   // Лишняя пустая строка.
	lexer(const std::string& file_path);
	void generate_tokens();
	std::vector<token>& get_tokens();
	void print_tokens();
};