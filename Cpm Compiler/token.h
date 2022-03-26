#pragma once
#include <string>
#include <vector>

enum class token_type {
	VAR, // ����������
	VAL, // ���������
	INPUT, // ������� �����
	PRINT, // ������� ������
	PLUS, // ����
	MINUS, // �����
	EQUAL, // �����
	SEMICOLON, // ����� � �������
	LEFT_B, // ����� ������
	RIGHT_B, // ������ ������
	IDENTIFIER, // ���
	LITERAL, // �������
	QUOTE // �������
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