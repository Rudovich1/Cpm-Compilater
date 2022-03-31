#pragma once
#include "cpm_compiler.h"
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include "AST.h"
#include "AST_abstract_nodes.h"
#include "AST_nodes.h"
#include "commands.h"
#include "compiler_errors.h"
#include "cpp_generator.h"
#include "lexer.h"
#include "log.h"
#include "semanticer.h"
#include "syntaxer.h"
#include "token.h"

class cpm_compiler{
public:

	static void compilation(std::string file_path);

};

