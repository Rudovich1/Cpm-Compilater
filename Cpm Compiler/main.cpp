#include <iostream>
#include <fstream>
#include <string>
#include "cpm_compiler.h"

using namespace std;

int main() {
	string file_path = "code.cpm";
	cpm_compiler cpm(file_path);

	cpm.compilation();
	cpm.lexer_data();
}