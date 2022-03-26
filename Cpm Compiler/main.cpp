#include <iostream>
#include <fstream>
#include "lexer.h"

#define DEBUG

using namespace std;

int main() {

	string file_path = "code.cpm";
	lexer lex(file_path);
	lex.generate_tokens();
	lex.print_tokens();
}