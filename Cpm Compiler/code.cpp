#include "cpm_runtime.h"
int main()
{
	mixed str;
	str = "Hello";
	str = (str + "!");
	cpm_print(str);
	str = ((21 + 2) + 18);
	cpm_print(str);
	mixed worldString;
	worldString = "World";
	mixed answerNumber;
	answerNumber = 42;
	cpm_print((worldString + answerNumber));
	cpm_print((worldString - answerNumber));
	mixed pi;
	pi = 3.14;
	cpm_print((pi + answerNumber));
	mixed numberString;
	numberString = 134;
	cpm_print((numberString - answerNumber));
	cpm_print((numberString + answerNumber));
	mixed name;
	name = cpm_input("Name: ");
	cpm_print(("Your name is " + name));
}