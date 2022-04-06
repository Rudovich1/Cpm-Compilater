#include "lexer.h"
#include "syntaxer.h"
#include "semanticer.h"
#include "cpp_generator.h"
#include "log.h"

int main(int argc, char* argv[]) {
	try {
		std::string file_path = argv[1];

		lexer Lexer(file_path);
		Lexer.generate_tokens();

		syntaxer Syntaxer(Lexer.get_tokens());
		Syntaxer.command_generation();

		semanticer Semanticer(Syntaxer.get_commands());
		Semanticer.semantic_verification();

       		while (file_path[file_path.size() - 1] != '.')
		{
			file_path.resize(file_path.size() - 1);
		}
        	file_path.resize(file_path.size() - 1);

        	std::string file_name = argv[0];
		while (file_name[file_name.size() - 1] != '\\')
		{
			file_name.resize(file_name.size() - 1);
		}
        	std::string name;
        	while (file_path[file_path.size() - 1] != '\\')
		{
			name = file_path[file_path.size() - 1] + name;
            		file_path.resize(file_path.size() - 1);
		}
        	file_name += name;
		char _name_[file_name.size()];
		for (int i = 0;i<file_name.size();++i)
		{
			_name_[i] = file_name[i];
		}
		cpp_generator Cpp_generator(Syntaxer.get_commands(), file_name);
		Cpp_generator.generate_cpp_code();
		system(("g++ -o " + file_path + name + " " + file_name + ".cpp & " + file_path + name +".exe").c_str());
	}
	catch (const std::string error_information) 
	{

		//file_logging::to_log(error_information);
		stream_logging::to_log(error_information);

	}
}