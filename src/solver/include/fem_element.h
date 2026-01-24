#pragma once
#include "types.h"
#include <Eigen/Dense>

Eigen::Matrix<double, 6, 6> element_stiffness(double E, double nu, double t,
                                              const Nodes &nodes,
                                              const Element &e);

Eigen::Vector3d element_stress(double E, double nu, const Nodes &nodes,
                               const Element &e, const Eigen::VectorXd &u);