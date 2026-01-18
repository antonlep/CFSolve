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

struct Res {
  Nodes nodes;
  Elems elems;
  std::vector<size_t> ind_zero;
  std::vector<double> u_initial;
  std::vector<double> F;
};

Res read_file(std::string filename);

#endif