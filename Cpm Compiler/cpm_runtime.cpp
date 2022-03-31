#include "cpm_runtime.h"

void cpm_print(const mixed& var)
{
	std::cout << var;
}

mixed cpm_input(const mixed& var)
{
	std::cout << var;
	mixed in;
	std::cin >> in;
	return in;
}

mixed cpm_input()
{
	mixed in;
	std::cin >> in;
	return in;
}
