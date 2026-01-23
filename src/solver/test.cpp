#include "fem.h"
#include <iostream>

int main() {

  SolverOutput result = solve_from_file("fem.inp");

  for (std::vector<double> r : result.stress) {
    std::cout << r[0] << " " << r[1] << " " << r[2] << std::endl;
  }

  return 0;
}