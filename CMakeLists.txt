cmake_minimum_required(VERSION 3.14)
project(Snippets)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(templates/ds)
include_directories(templates/graph)
include_directories(templates/graph_ds)
include_directories(templates/math)
include_directories(templates/string_ds)

add_executable(Snippets main.cpp template_tests/rand.h template_tests/template_utils.h template_tests/tests.h template_tests/test_utils.h template_tests/ds/rsq.h template_tests/ds/ds_tests.h template_tests/graph/graph_tests.h)
