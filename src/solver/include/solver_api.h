#pragma once
#include "types.h"

SolverOutput solve_from_data(const SolverInput &input);
SolverOutput solve_from_file(const char *path);