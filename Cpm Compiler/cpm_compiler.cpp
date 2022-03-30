#include "cpm_compiler.h"

#define my_DEBUG

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

	}
	catch (const std::string error_information) {

		file_logging::to_log(error_information);
		stream_logging::to_log(error_information);

	}
}
