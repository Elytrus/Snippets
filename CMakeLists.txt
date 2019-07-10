cmake_minimum_required(VERSION 3.14)
project(Snippets)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(ds)
include_directories(graph_ds)

add_executable(Snippets
        ds/bit.h
        ds/segment_tree.h
        ds/sparse_table.h
        graph_ds/union_find.h
        main.cpp
        stdincludes.h math/extended_euclidian_algorithm.h string_ds/suffix_array.h)
