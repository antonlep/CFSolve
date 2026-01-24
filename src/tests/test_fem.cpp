#include "solver_api.h"
#include <cassert>

int main() {
  SolverInput in;

  in.nodes = {{0, 0}, {1, 0}, {0, 1}};
  in.elements = {{0, 1, 2}};
  in.fixed_dofs = {0, 1, 2, 3};
  in.fixed_values = {0, 0, 0, 0};
  in.forces = {0, 0, 0, 0, 100, 0};

  SolverOutput out = fem_solve(in);

  assert(out.stress.size() == 1);
  assert(out.disp.size() == 3);
}