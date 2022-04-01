#include "cpm_runtime.cpp"
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
}