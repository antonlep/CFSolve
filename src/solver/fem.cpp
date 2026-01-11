#include "Eigen/Core"
#include <Eigen/Dense>
#include <iostream>

struct Node {
  float x;
  float y;
};

float area(Node i, Node j, Node k) {
  return 0.5 * (i.x * (j.y - k.y) + j.x * (k.y - i.y) + k.x * (i.y - j.y));
}

Eigen::MatrixXd stiffness_matrix(float E, float v, float t, Node nodes[3]) {
  Node i = nodes[0];
  Node j = nodes[1];
  Node k = nodes[2];
  float A = area(i, j, k);

  Eigen::MatrixXd B(3, 6);
  Eigen::MatrixXd D(3, 3);
  Eigen::MatrixXd K(6, 6);

  B << j.y - k.y, 0, k.y - i.y, 0, i.y - j.y, 0, 0, k.x - j.x, 0, i.x - k.x, 0,
      j.x - i.x, k.x - j.x, j.y - k.y, i.x - k.x, k.y - i.y, j.x - i.x,
      i.y - j.y;
  B *= 1 / (2 * A);

  D << 1, v, 0, v, 1, 0, 0, 0, (1 - v) / 2;
  D *= E / (1 - v * v);

  K = t * A * B.transpose() * D * B;
  return K;
}

Eigen::MatrixXd update_global_stiffness(Eigen::MatrixXd K, Eigen::MatrixXd k,
                                        int order[3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      K(order[i] * 2, order[j] * 2) += k(i * 2, j * 2);
      K(order[i] * 2, order[j] * 2 + 1) += k(i * 2, j * 2 + 1);
      K(order[i] * 2 + 1, order[j] * 2) += k(i * 2 + 1, j * 2);
      K(order[i] * 2 + 1, order[j] * 2 + 1) += k(i * 2 + 1, j * 2 + 1);
    }
  }
  return K;
}

int add(int a, int b) { return a + b; }

float plate(float h, float w, float t, float f) {
  float E = 210E6;
  float v = 0.3;
  f = 0.5 * f;
  Node p1 = {0, 0};
  Node p2 = {0, 10};
  Node p3 = {20, 10};
  Node p4 = {20, 0};
  Node nodes1[3] = {p1, p3, p2};
  Node nodes2[3] = {p1, p4, p3};
  int order1[3] = {0, 2, 1};
  int order2[3] = {0, 3, 2};
  int size = 4;
  Eigen::MatrixXd K = Eigen::MatrixXd::Zero(size * 2, size * 2);

  Eigen::MatrixXd K1 = stiffness_matrix(E, v, t, nodes1);
  K = update_global_stiffness(K, K1, order1);

  Eigen::MatrixXd K2 = stiffness_matrix(E, v, t, nodes2);
  K = update_global_stiffness(K, K2, order2);

  std::cout << "K" << std::endl;
  std::cout << K << std::endl;

  std::vector<int> ind_nonzero{4, 5, 6, 7};
  Eigen::MatrixXd K_nonzero;
  K_nonzero = K(ind_nonzero, ind_nonzero);

  std::cout << "K_nonzero" << std::endl;
  std::cout << K_nonzero << std::endl;

  Eigen::VectorXd F(4);
  F << f, 0, f, 0;
  Eigen::VectorXd u = K_nonzero.colPivHouseholderQr().solve(F);
  std::cout << "u" << std::endl;
  std::cout << u << std::endl;

  return u[0];
}
