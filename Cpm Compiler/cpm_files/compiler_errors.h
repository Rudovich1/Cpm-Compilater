#pragma once

#include <string>

enum class compiler_errors_type {
    LEXER,
    PARSER,
    SEMANTIC,
    SYNTAXER,
    CODE_GENERATION
};

class compiler_errors {

public:

    static void error_message(compiler_errors_type error_type, const std::string& message, const std::pair<int, int>& error_coordinate = { -1,-1 });
};


