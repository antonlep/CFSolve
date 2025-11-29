#include <pybind11/pybind11.h>
#include "fem.h"

// int add(int a, int b)
// {
//     return a + b;
// }

PYBIND11_MODULE(solver, m)
{
    // py::class_<Mesh>(m, "Mesh")
    //     .def(py::init<>())
    //     .def_readwrite("nodes", &Mesh::nodes)
    //     .def_readwrite("elements", &Mesh::elements);

    // m.def("solve_poisson", &solve_poisson, "A function that solves poisson equation");

    m.def("add", &add, "A function that adds two numbers", pybind11::arg("a"), pybind11::arg("b"));
}
