#include "fem.h"
#include "read_file.h"
#include <iostream>

int main() {

  SolverInput input = read_file("fem2.inp");

  std::cout << solve(input) << std::endl;

  return 0;
}