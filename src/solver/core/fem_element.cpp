#include "fem_element.h"
#include <Eigen/Dense>

static double area(const Node &a, const Node &b, const Node &c) {
  return 0.5 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}

Eigen::Matrix<double, 6, 6> element_stiffness(double E, double nu, double t,
                                              const Nodes &nodes,
                                              const Element &e) {
  const Node &i = nodes[e[0]];
  const Node &j = nodes[e[1]];
  const Node &k = nodes[e[2]];

  double A = area(i, j, k);

  Eigen::Matrix<double, 3, 6> B;
  B << j.y - k.y, 0, k.y - i.y, 0, i.y - j.y, 0, 0, k.x - j.x, 0, i.x - k.x, 0,
      j.x - i.x, k.x - j.x, j.y - k.y, i.x - k.x, k.y - i.y, j.x - i.x,
      i.y - j.y;

  B /= (2 * A);

  Eigen::Matrix3d D;
  D << 1, nu, 0, nu, 1, 0, 0, 0, (1 - nu) / 2;

  D *= E / (1 - nu * nu);

  return t * A * B.transpose() * D * B;
}

Eigen::Vector3d element_stress(double E, double nu, const Nodes &nodes,
                               const Element &e, const Eigen::VectorXd &u) {
  Eigen::Matrix<double, 6, 1> ue;
  for (size_t i = 0; i < 3; i++) {
    ue(2 * i) = u(2 * e[i]);
    ue(2 * i + 1) = u(2 * e[i] + 1);
  }

  double A = area(nodes[e[0]], nodes[e[1]], nodes[e[2]]);

  Eigen::Matrix<double, 3, 6> B;
  B << nodes[e[1]].y - nodes[e[2]].y, 0, nodes[e[2]].y - nodes[e[0]].y, 0,
      nodes[e[0]].y - nodes[e[1]].y, 0, 0, nodes[e[2]].x - nodes[e[1]].x, 0,
      nodes[e[0]].x - nodes[e[2]].x, 0, nodes[e[1]].x - nodes[e[0]].x,
      nodes[e[2]].x - nodes[e[1]].x, nodes[e[1]].y - nodes[e[2]].y,
      nodes[e[0]].x - nodes[e[2]].x, nodes[e[2]].y - nodes[e[0]].y,
      nodes[e[1]].x - nodes[e[0]].x, nodes[e[0]].y - nodes[e[1]].y;

  B /= (2 * A);

  Eigen::Matrix3d D;
  D << 1, nu, 0, nu, 1, 0, 0, 0, (1 - nu) / 2;

  D *= E / (1 - nu * nu);

  return D * B * ue;
}