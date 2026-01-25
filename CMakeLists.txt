cmake_minimum_required(VERSION 3.18)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(cfs LANGUAGES CXX)

enable_testing()

add_subdirectory(src/solver)
