#include "cpm_compiler.h"

void cpm_compiler::lexer_runtime(){

	Lexer.generate_lexer(file_path);
	Lexer.generate_tokens();

}

void cpm_compiler::lexer_data(){

	Lexer.print_tokens();

}

void cpm_compiler::syntaxer_runtime(){
	


}

void cpm_compiler::compilation(){
	try {
		lexer_runtime();
	}
	catch (const std::string error_information) {

		file_logging::to_log(error_information);
		stream_logging::to_log(error_information);

	}
}
