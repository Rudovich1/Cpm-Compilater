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
public:

	static void compilation(std::string file_path);

};

