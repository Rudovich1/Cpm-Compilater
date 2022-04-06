#pragma once
#include "cpm_runtime.h"

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
