cmake_minimum_required(VERSION 3.14)
project(Snippets)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(ds)
include_directories(graph)
include_directories(graph_ds)
include_directories(math)
include_directories(string_ds)

add_executable(Snippets main.cpp test/rand.h test/template_utils.h test/tests.h test/test_utils.h)
