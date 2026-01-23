#ifndef READ_FILE_H
#define READ_FILE_H

#include <Eigen/Dense>
#include <vector>
using Index = Eigen::Index;
using NodeId = Index;
struct Node {
  double x;
  double y;
};
using Nodes = std::vector<Node>;
using Elem = std::vector<NodeId>;
using Elems = std::vector<Elem>;

struct SolverInput {
  Nodes nodes;
  Elems elems;
  std::vector<size_t> u_indices;
  std::vector<double> u;
  std::vector<double> F;
};

struct SolverOutput {
  std::vector<std::vector<double>> stress;
  std::vector<std::vector<double>> disp;
};

SolverInput read_file(std::string filename);

#endif