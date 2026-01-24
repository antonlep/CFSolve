#pragma once
#include "Eigen/Core"
#include "types.h"
#include <Eigen/Dense>

struct FemResult {
  std::vector<Eigen::Vector3d> stress;
  std::vector<Eigen::Vector2d> disp;
}

FemResult
fem_solve(const Nodes &nodes, const Elems &elems,
          const std::vector<int> &fixed_dofs,
          const std::vector<double> &fixed_values,
          const Eigen::VectorXd &forces);