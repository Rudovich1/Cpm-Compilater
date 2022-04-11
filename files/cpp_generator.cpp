#pragma once
#include "cpp_generator.h"

void cpp_generator::generate_cpp_code()
{
   // А зачем такие сложности?
   // Можно просто:
   //   cpp_file << "#include \"cpm_runtime.h\"\n";
   //
   // Ты кажется запутался, когда нужно экранировать кавычку:
   // Ее нужно экранировать если литерал начинаться с нее, то есть:
   //   "'"
   //   "\""
   //   '"'
   //   '\''
	cpp_file << "#include " << '\"' << "cpm_runtime.h" << '\"' << '\n';
	cpp_file << "#include " << '\"' << "mixed.h" << '\"' << '\n';
	cpp_file << "#include " << '\"' << "compiler_errors.h" << '\"' << '\n';
	cpp_file << "#include <iostream>" << '\n';
	cpp_file << "#include <string>" << '\n';
   // Ни в коем случае не подключай cpp файлы!
   // https://stackoverflow.com/questions/1686204/why-should-i-not-include-cpp-files-and-instead-use-a-header
	cpp_file << "#include " << '\"' << "cpm_runtime.cpp" << '\"' << '\n';
	cpp_file << "#include " << '\"' << "mixed.cpp" << '\"' << '\n';
	cpp_file << "#include " << '\"' << "compiler_errors.cpp" << '\"' << '\n';

	cpp_file << "int main()" << '\n' << "{" << '\n';
	for (auto& command : commands)
	{
		cpp_file << '\t' << command->generate_cpp_command() << ";" << '\n';
	}
   // Здесь бы добавить табуляцию для этих строк, чтобы было форматирование.
	cpp_file << "system(\"pause\");\n;";
	cpp_file << "return(0);\n";
	cpp_file << "}";
	
	cpp_file.close();
}