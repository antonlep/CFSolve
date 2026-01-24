#include "solver_api.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(_solver /*unused*/, m /*unused*/) {
  py::class_<Node>(m, "Node")
      .def(py::init<double, double>())
      .def_readwrite("x", &Node::x)
      .def_readwrite("y", &Node::y);

  py::class_<SolverInput>(m, "SolverInput")
      .def(py::init<>())
      .def_readwrite("nodes", &SolverInput::nodes)
      .def_readwrite("elements", &SolverInput::elements)
      .def_readwrite("fixed_dofs", &SolverInput::fixed_dofs)
      .def_readwrite("fixed_values", &SolverInput::fixed_values)
      .def_readwrite("forces", &SolverInput::forces);

  py::class_<SolverOutput>(m, "SolverOutput")
      .def_readonly("stress", &SolverOutput::stress)
      .def_readonly("disp", &SolverOutput::disp);

  m.def("solve_from_data", &solve_from_data);

  m.def("solve_from_file", &solve_from_file);
}
