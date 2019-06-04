cmake_minimum_required(VERSION 3.14)
project(Snippets)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(ds)
include_directories(graph-ds)

add_executable(Snippets
        ds/bit.h
        ds/segment_tree.h
        ds/sparse_table.h
        graph-ds/union_find.h
        main.cpp
        stdincludes.h)
