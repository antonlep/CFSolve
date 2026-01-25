#define CATCH_CONFIG_MAIN
#include "solver_api.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Single element tension") {
  SolverInput in;

  in.nodes = {{0.0, 0.0}, {0, 10.0}, {20, 10}};

  in.elements = {{0, 2, 1}};

  in.fixed_dofs = {0, 1};
  in.fixed_values = {0.0, 0.0};

  in.forces = {0.0, 0.0, 0.0, 0.0, 10.0, 0.0};

  SolverOutput out = solve_from_data(in);

  REQUIRE(out.disp.size() == 3);
  REQUIRE(out.disp[2][0] > 0.0); // positive displacement
}