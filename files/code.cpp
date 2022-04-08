#include "cpm_runtime.h"
#include "mixed.h"
#include "compiler_errors.h"
#include <iostream>
#include <string>
#include "cpm_runtime.cpp"
#include "mixed.cpp"
#include "compiler_errors.cpp"
int main()
{
	mixed str = mixed("Hello");
	str = (str + mixed("!"));
	cpm_print(str);
	str = ((mixed(21) + mixed(2)) + mixed(18));
	cpm_print(str);
	const mixed worldString = mixed("World");
	const mixed answerNumber = mixed(42);
	cpm_print((worldString + answerNumber));
	cpm_print((worldString - answerNumber));
	const mixed pi = mixed(3.14);
	cpm_print((pi + answerNumber));
	const mixed numberString = mixed(134);
	cpm_print((numberString - answerNumber));
	cpm_print((numberString + answerNumber));
	const mixed name = cpm_input(mixed("Name: "));
	cpm_print((mixed("Your name is ") + name));
	cpm_print((((mixed(5) + mixed(5)) - mixed(1.1)) + pi));
	cpm_print((mixed("asd") - worldString));
system("pause");
;return(0);
}