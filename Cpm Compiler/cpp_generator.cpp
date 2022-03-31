#include "cpp_generator.h"

void cpp_generator:: generate_cpp_code()
{
	cpp_file << "#include " << '\"' << cpm_runtime_path << '\"' << '\n';
	cpp_file << "void cpm_code()" << '\n' << "{" << '\n';
	for (auto& command : commands) 
	{
		cpp_file << '\t' << command->generate_cpp_command() << ";" << '\n';
	}
	cpp_file << "}";
	cpp_file.close();
}
