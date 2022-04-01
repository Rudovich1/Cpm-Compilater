#pragma once
#include "cpp_generator.h"

void cpp_generator::generate_cpp_code()
{
	cpp_file << "#include " << '\"' << "cpm_runtime.h" << '\"' << '\n';
	cpp_file << "#include " << '\"' << "mixed.h" << '\"' << '\n';
	cpp_file << "#include " << '\"' << "compiler_errors.h" << '\"' << '\n';
	cpp_file << "#include <iostream>" << '\n';
	cpp_file << "#include <string>" << '\n';
	cpp_file << "#include " << '\"' << "cpm_runtime.cpp" << '\"' << '\n';
	cpp_file << "#include " << '\"' << "mixed.cpp" << '\"' << '\n';
	cpp_file << "#include " << '\"' << "compiler_errors.cpp" << '\"' << '\n';

	cpp_file << "int main()" << '\n' << "{" << '\n';
	for (auto& command : commands)
	{
		cpp_file << '\t' << command->generate_cpp_command() << ";" << '\n';
	}
	cpp_file << "}";
	cpp_file.close();
}