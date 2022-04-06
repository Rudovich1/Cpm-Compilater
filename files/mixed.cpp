#pragma once
#include "mixed.h"

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