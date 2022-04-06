#pragma once
#include "mixed.h"
#include <iostream>
#include "compiler_errors.h"

void cpm_print(const mixed& var, char end = '\n');
mixed cpm_input();
mixed cpm_input(const mixed& var);