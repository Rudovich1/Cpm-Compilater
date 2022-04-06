#pragma once
#include "semanticer.h"

void semanticer::semantic_verification()
{
	for (auto &command : this->commands) 
	{
		command->semantic_verification(this->vals, this->vars);
	}
}
