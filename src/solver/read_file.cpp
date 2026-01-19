#include "read_file.h"
#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

SolverInput read_file(std::string filename) {

  std::fstream myfile;

  myfile.open(filename);
  std::vector<std::string> g1;
  Nodes nodes;
  Elems elems;
  std::vector<size_t> u_indices;
  std::vector<double> u;
  std::vector<double> F;

  if (myfile.is_open()) {
    std::string str;
    bool read = false;
    while (std::getline(myfile, str)) {
      if (str.rfind("nodes", 0) == 0) {
        read = true;
        std::getline(myfile, str);
      }
      if (str == "") {
        read = false;
      }
      if (read == true) {
        std::istringstream iss(str);
        double x, y;
        char sep = ',';
        iss >> x >> sep >> y;
        nodes.push_back(Node{x, y});
      }
    }
    myfile.clear();
    myfile.seekg(0);
    read = false;
    while (std::getline(myfile, str)) {
      if (str.rfind("elements", 0) == 0) {
        read = true;
        std::getline(myfile, str);
      }
      if (str == "") {
        read = false;
      }
      if (read == true) {
        std::istringstream iss(str);
        int n1, n2, n3;
        char sep = ',';
        iss >> n1 >> sep >> n2 >> sep >> n3;
        elems.push_back(Elem{n1, n2, n3});
      }
    }
    myfile.clear();
    myfile.seekg(0);
    read = false;
    while (std::getline(myfile, str)) {
      if (str.rfind("displacements", 0) == 0) {
        read = true;
        std::getline(myfile, str);
      }
      if (str == "") {
        read = false;
      }
      if (read == true) {
        int node, coord;
        double disp;
        std::istringstream iss(str);
        char sep = ',';
        iss >> node >> sep >> coord >> sep >> disp;
        u_indices.push_back(node * 2 + coord);
        u.push_back(disp);
      }
    }
    myfile.clear();
    myfile.seekg(0);
    read = false;
    F.insert(F.begin(), nodes.size() * 2, 0);
    while (std::getline(myfile, str)) {
      if (str.rfind("forces", 0) == 0) {
        read = true;
        std::getline(myfile, str);
      }
      if (str == "") {
        read = false;
      }
      if (read == true) {
        int node, coord;
        double force;
        std::istringstream iss(str);
        char sep = ',';
        iss >> node >> sep >> coord >> sep >> force;
        F[node * 2 + coord] = force;
      }
    }
    myfile.close();
  }

  SolverInput input = {nodes, elems, u_indices, u, F};
  return input;
}