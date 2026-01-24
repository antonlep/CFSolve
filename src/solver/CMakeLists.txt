cmake_minimum_required(VERSION 3.18)
project(solver LANGUAGES CXX)

find_package(pybind11 REQUIRED)

add_library(solver_core
    core/fem_element.cpp
    core/fem_solve.cpp
    io/read_file.cpp
    api/solver_api.cpp
)

target_include_directories(solver_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen
)

pybind11_add_module(_solver
    bindings.cpp
)

target_link_libraries(_solver PRIVATE solver_core)

install(
  TARGETS _solver
  LIBRARY DESTINATION solver
)

install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py
  DESTINATION solver
)