#include "lexer.h"
#include "syntaxer.h"
#include "semanticer.h"
#include "cpp_generator.h"
#include "log.h"

// Не уверен, что этот файл должен называться так, лучше просто main.cpp, так его проще найти!
int main(int argc, char* argv[]) {
	try {

		if (argc == 1)
		{
         // Почему ты кидаешь не исключение, а строку?
         // Здесь должно бросать одно из стандартных исключений с
         // этим сообщением.
         // А вообще лучше здесь выводить просто ошибку и подсказку
         // как использовать твою программу и делать просто return 1.
			throw((std::string)("There is no path to the file"));
		}

		std::string file_path = argv[1];

      // Имена переменных должны быть в lowerCamelCase!
		lexer Lexer(file_path);
		Lexer.generate_tokens();

      // А где у тебя отдельный этап генерации AST? Он должен быть отдельно
      // так как AST используется в генераторе кода и его проверке.
		syntaxer Syntaxer(Lexer.get_tokens());
      // Если это он, то странно что у него не метод parse, а command_generation.
		Syntaxer.command_generation();

		semanticer Semanticer(Syntaxer.get_commands());
		Semanticer.semantic_verification();

      // Все еще проблемы с форматированием.
      // Также я не понимаю что тут делается, это 100%
      // плохой алгоритм!
        while (file_path[file_path.size() - 1] != '.')
		{
			file_path.resize(file_path.size() - 1);
		}
        file_path.resize(file_path.size() - 1);

        std::string file_name = argv[0];

		while (file_name.size() > 0 && file_name[file_name.size() - 1] != '\\')
		{
			file_name.resize(file_name.size() - 1);
		}

        std::string name;
        while (file_path.size() > 0 && file_path[file_path.size() - 1] != '\\')
		{
			name = file_path[file_path.size() - 1] + name;
            file_path.resize(file_path.size() - 1);
		}

        file_name += name;
		cpp_generator Cpp_generator(Syntaxer.get_commands(), file_name);
		Cpp_generator.generate_cpp_code();
		system(("g++ -o " + file_path + name + " " + file_name + ".cpp").c_str());
	}
	catch (const std::string error_information) {

		//file_logging::to_log(error_information);
		stream_logging::to_log(error_information);
		system("pause");
	}

	return 0;
}