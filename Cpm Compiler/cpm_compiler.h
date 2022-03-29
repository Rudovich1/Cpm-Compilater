#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include "log.h"
#include "compiler_errors.h"
#include "lexer.h"
#include "syntaxer.h"

class cpm_compiler{

	const std::string file_path;
	lexer Lexer;

	void lexer_runtime();
	void syntaxer_runtime();

public:

	cpm_compiler(const std::string& file_path) : file_path(file_path){}
	void lexer_data();
	void compilation();

};

