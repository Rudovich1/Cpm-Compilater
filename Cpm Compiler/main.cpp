#include <iostream>
#include <string>
#include "Cpm_headers\cpm_compiler.hpp"
#include "cpm_compiler.cpp"

using namespace std;

int main() 
{
	string file_path = "D:\\Visual Studio Code solutions\\GitHub\\Cpm-Compiler\\Cpm Compiler\\code.cpm";
	cpm_compiler::compilation(file_path);
}