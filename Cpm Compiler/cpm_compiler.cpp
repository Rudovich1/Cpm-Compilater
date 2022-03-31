#include "Cpm_headers\cpm_compiler.hpp"
#include "Cpm_headers\lexer.hpp"
#include "Cpm_headers\syntaxer.hpp"
#include "Cpm_headers\semanticer.hpp"
#include "Cpm_headers\cpp_generator.hpp"
#include "Cpm_headers\log.hpp"

//#define my_DEBUG

void cpm_compiler::compilation(std::string file_path) {
	try {
		lexer Lexer(file_path);
		Lexer.generate_tokens();

#ifdef my_DEBUG

		Lexer.print_tokens();

#endif

		syntaxer Syntaxer(Lexer.get_tokens());
		Syntaxer.command_generation();

#ifdef my_DEBUG

		Syntaxer.print_commands();

#endif
		semanticer Semanticer(Syntaxer.get_commands());
		Semanticer.semantic_verification();

		std::string file_name = file_path;
		while (file_name[file_name.size() - 1] != '.') 
		{
			file_name.resize(file_name.size() - 1);
		}
		file_name.resize(file_name.size() - 1);

		cpp_generator Cpp_generator(Syntaxer.get_commands(), file_name);
		Cpp_generator.generate_cpp_code();
	}
	catch (std::string error_information) {

		file_logging::to_log(error_information);
		stream_logging::to_log(error_information);

	}
}
