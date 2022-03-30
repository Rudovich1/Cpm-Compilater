#include <iostream>
#include <string>
#include "cpm_compiler.h"

using namespace std;

int main() {
	string file_path = "code.cpm";
	cpm_compiler::compilation(file_path);
}