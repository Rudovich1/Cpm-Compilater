#include "semanticer.h"

void semanticer::semantic_verification()
{
	for (auto &command : commands) 
	{
		command->semantic_verification(this->vals, this->vars);
	}
}
