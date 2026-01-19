#include "fem.h"
#include "read_file.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(solver /*unused*/, m /*unused*/) {
  // py::class_<Mesh>(m, "Mesh")
  //     .def(py::init<>())
  //     .def_readwrite("nodes", &Mesh::nodes)
  //     .def_readwrite("elements", &Mesh::elements);

  // m.def("solve_poisson", &solve_poisson, "A function that solves poisson
  // equation");

  m.def("add", &add, "A function that adds two numbers", py::arg("a"),
        py::arg("b"));

  m.def("solve_from_data", &solve_from_data, "solve from data",
        py::arg("node_coords"), py::arg("elements"), py::arg("u_indices"),
        py::arg("u"), py::arg("f"));
}
