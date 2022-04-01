#include "lexer.h"
#include "syntaxer.h"
#include "semanticer.h"
#include "cpp_generator.h"
#include "log.h"

int main() {
	try {
		std::string file_path = "code.cpm";

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

		std::string file_name = "code";

		cpp_generator Cpp_generator(Syntaxer.get_commands(), file_name);
		Cpp_generator.generate_cpp_code();
		system(("g++ -o " + file_name + " " + file_name + ".cpp & code.exe").c_str());
		system(("del " + file_name + ".cpp").c_str());
	}
	catch (const std::string error_information) {

		//file_logging::to_log(error_information);
		stream_logging::to_log(error_information);

	}
}


