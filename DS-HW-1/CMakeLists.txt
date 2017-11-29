cmake_minimum_required(VERSION 3.7)
project(DS_HW-1)

set(CMAKE_CXX_STANDARD 11)
set(COVERAGE_COMPILE_FLAGS "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_COMPILE_FLAGS}")

set(SOURCE_FILES
        Splay_Tree.h
        tests/tree_tests.cpp
        )
add_executable(DS_HW_1 ${SOURCE_FILES})