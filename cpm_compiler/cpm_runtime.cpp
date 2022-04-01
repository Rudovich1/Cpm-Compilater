#include <string>
#include <iostream>
#include <exception>

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

enum class mixed_type
{
	INT,
	FLOAT,
	STRING

};

union mixed_data
{
	long long Int;
	double Float;
	std::string String;

	mixed_data() : String(""){}
	~mixed_data() {}
};

class mixed 
{
	mixed_data data;
	mixed_type type;

public:
	mixed() : type(mixed_type::STRING) {};
	mixed(int var);
	mixed(long long var);
	mixed(double var);
	mixed(const std::string& var);
	mixed(const char* var);
	mixed(const mixed& var);

	friend mixed operator+(const mixed& var1, const mixed& var2);
	friend mixed operator-(const mixed& var1, const mixed& var2);
	void operator= (const mixed& var);

	friend void cpm_print(const mixed& var, char end);
	friend mixed cpm_input(const mixed& var);
	friend mixed cpm_input();
};

void cpm_print(const mixed& var, char end);
mixed cpm_input();
mixed cpm_input(const mixed& var);

mixed operator+(const mixed& var1, const mixed& var2)
{
	if (var1.type == mixed_type::FLOAT)
	{
		if (var2.type == mixed_type::FLOAT) 
		{
			return mixed(var1.data.Float + var2.data.Float);
		}
		if (var2.type == mixed_type::INT)
		{
			return mixed(var1.data.Float + var2.data.Int);
		}
		if (var2.type == mixed_type::STRING)
		{
			return mixed(std::to_string(var1.data.Float) + var2.data.String);
		}
	}
	else if (var1.type == mixed_type::INT)
	{
		if (var2.type == mixed_type::FLOAT)
		{
			return mixed(var1.data.Int + var2.data.Float);
		}
		if (var2.type == mixed_type::INT)
		{
			return mixed(var1.data.Int + var2.data.Int);
		}
		if (var2.type == mixed_type::STRING)
		{
			return mixed(std::to_string(var1.data.Int) + var2.data.String);
		}
	}
	if (var1.type == mixed_type::STRING)
	{
		if (var2.type == mixed_type::FLOAT)
		{
			return mixed(var1.data.String + std::to_string(var2.data.Float));
		}
		if (var2.type == mixed_type::INT)
		{
			return mixed(var1.data.String + std::to_string(var2.data.Int));
		}
		if (var2.type == mixed_type::STRING)
		{
			return mixed(var1.data.String + var2.data.String);
		}
	}
	compiler_errors::error_message(compiler_errors_type::CODE_GENERATION, "unknown type");
	return mixed();
}

mixed operator-(const mixed& var1, const mixed& var2)
{
	if (var1.type == mixed_type::FLOAT)
	{
		if (var2.type == mixed_type::FLOAT)
		{
			return mixed(var1.data.Float - var2.data.Float);
		}
		if (var2.type == mixed_type::INT)
		{
			return mixed(var1.data.Float - var2.data.Int);
		}
		if (var2.type == mixed_type::STRING)
		{
			try 
			{
				return mixed(var1.data.Float - std::stoll(var2.data.String));
			}
			catch (std::exception)
			{
				try
				{
					return mixed(var1.data.Float - std::stod(var2.data.String));
				}
				catch (std::exception)
				{
				}
			}
			return mixed(var1.data.Float);

		}
	}
	else if (var1.type == mixed_type::INT)
	{
		if (var2.type == mixed_type::FLOAT)
		{
			return mixed(var1.data.Int - var2.data.Float);
		}
		if (var2.type == mixed_type::INT)
		{
			return mixed(var1.data.Int - var2.data.Int);
		}
		if (var2.type == mixed_type::STRING)
		{
			try
			{
				return mixed(var1.data.Int - std::stoll(var2.data.String));
			}
			catch (std::exception)
			{
				try
				{
					return mixed(var1.data.Int - std::stod(var2.data.String));
				}
				catch (std::exception)
				{
				}
			}
			return mixed(var1.data.Int);

		}
	}
	if (var1.type == mixed_type::STRING)
	{
		if (var2.type == mixed_type::FLOAT)
		{
			try
			{
				return mixed(std::stoll(var1.data.String) - var2.data.Float);
			}
			catch (std::exception)
			{
				try
				{
					return mixed(std::stod(var1.data.String) - var2.data.Float);
				}
				catch (std::exception)
				{
				}
			}
			return mixed(-var2.data.Float);
		}
		if (var2.type == mixed_type::INT)
		{
			try
			{
				return mixed(std::stoll(var1.data.String) - var2.data.Int);
			}
			catch (std::exception)
			{
				try
				{
					return mixed(std::stod(var1.data.String) - var2.data.Int);
				}
				catch (std::exception)
				{
				}
			}
			return mixed(-var2.data.Int);
		}
		if (var2.type == mixed_type::STRING)
		{
			try{
				try
				{
					try
					{
						return mixed(std::stoll(var1.data.String) - std::stoll(var2.data.String));
					}
					catch (std::exception)
					{
						try
						{
							return mixed(std::stoll(var1.data.String) - std::stod(var2.data.String));
						}
						catch (std::invalid_argument)
						{
						}
					}
					return mixed(std::stoll(var1.data.String));
				}
				catch (std::exception)
				{
					try
					{
						return mixed(std::stod(var1.data.String) - std::stoll(var2.data.String));
					}
					catch (std::exception)
					{
						try
						{
							return mixed(std::stod(var1.data.String) - std::stod(var2.data.String));
						}
						catch (std::exception)
						{
						}
					}
					return mixed(std::stod(var1.data.String));
				}
			}
			catch(std::exception){
				try
				{
					return mixed(-std::stoll(var2.data.String));
				}
				catch (std::exception)
				{
					try
					{
						return mixed(-std::stod(var2.data.String));
					}
					catch (std::exception)
					{
					}
				}
			}
			return mixed(0);
		}
	}
	compiler_errors::error_message(compiler_errors_type::CODE_GENERATION, "unknown type");
	return mixed();
}

mixed::mixed(int var) : type(mixed_type::INT)
{
	data.Int = var;
}

mixed::mixed(long long var) : type(mixed_type::INT)
{
	data.Int = var;
}

mixed::mixed(double var) : type(mixed_type::FLOAT)
{
	data.Float = var;
}

mixed::mixed(const std::string& var) : type(mixed_type::STRING)
{
	data.String = var;
}

mixed::mixed(const char* var) : type(mixed_type::STRING)
{
	data.String = var;
}

mixed::mixed(const mixed& var) : type(var.type)
{
	if (var.type == mixed_type::FLOAT)
	{
		data.Float = var.data.Float;
		return;
	}
	else if (var.type == mixed_type::INT)
	{
		data.Int = var.data.Int;
		return;
	}
	else if (var.type == mixed_type::STRING)
	{
		data.String = var.data.String;
		return;
	}
	compiler_errors::error_message(compiler_errors_type::CODE_GENERATION, "unknown type");
}

void mixed::operator=(const mixed& var)
{
	if (var.type == mixed_type::FLOAT) 
	{
		type = var.type;
		data.Float = var.data.Float;
		return;
	} 
	else if (var.type == mixed_type::INT)
	{
		type = var.type;
		data.Int = var.data.Int;
		return;
	}
	else if (var.type == mixed_type::STRING)
	{
		type = var.type;
		data.String = var.data.String;
		return;
	}
	compiler_errors::error_message(compiler_errors_type::CODE_GENERATION, "unknown type");
}

void cpm_print(const mixed& var, char end = '\n')
{
	if (var.type == mixed_type::FLOAT) 
	{
		std::cout << var.data.Float << end;
		return;
	}
	else if (var.type == mixed_type::INT)
	{
		std::cout << var.data.Int << end;
		return;
	}
	else if (var.type == mixed_type::STRING)
	{
		std::cout << var.data.String << end;
		return;
	}
	compiler_errors::error_message(compiler_errors_type::CODE_GENERATION, "unknown type");
}

mixed cpm_input()
{
	std::string temp;
	std::cin >> temp;
	try
	{
		return mixed(std::stoll(temp));
	}
	catch (std::exception)
	{
		try
		{
			return mixed(std::stod(temp));
		}
		catch (std::exception)
		{
		}
	}
	return mixed(temp);
}

mixed cpm_input(const mixed& var)
{
	if (var.type == mixed_type::FLOAT)
	{
		std::cout << var.data.Float;
	}
	else if (var.type == mixed_type::INT)
	{
		std::cout << var.data.Int;
	}
	else if (var.type == mixed_type::STRING)
	{
		std::cout << var.data.String;
	}
	std::string temp;
	std::cin >> temp;
	try
	{
		return mixed(std::stoll(temp));
	}
	catch (std::exception)
	{
		try
		{
			return mixed(std::stod(temp));
		}
		catch (std::exception)
		{
		}
	}
	return mixed(temp);
}


void compiler_errors::error_message(compiler_errors_type error_type, const std::string& message, const std::pair<int, int>& error_coordinate)
{
	std::string error_information;

	switch (error_type)
	{
	case compiler_errors_type::LEXER: {
		error_information = "Lexical error: ";
	}
	case compiler_errors_type::PARSER: {
		error_information = "Syntax error: ";
	}
	case compiler_errors_type::SEMANTIC: {
		error_information = "Semantic error: ";
	}
	case compiler_errors_type::CODE_GENERATION: {
		error_information = "Generation error: ";
	}
	default:
		error_information = "Unknown error: ";
	}

	error_information += message + "!" + '\n';
	if (error_coordinate.first != -1) {
		error_information += "Line: " + std::to_string(error_coordinate.first) + ", Position : " + std::to_string(error_coordinate.second);
	}

	throw(error_information);
}