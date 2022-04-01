#pragma once
#include <string>
#include "compiler_errors.h"

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