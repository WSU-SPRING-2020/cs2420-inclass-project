cmake_minimum_required(VERSION 3.10)
project(assignment02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(graph src/graph.cpp)
add_executable(avl src/avl.cpp)
add_executable(bst src/bst.cpp)
add_executable(sort src/sort.cpp)
add_executable(demosq src/demosq.cpp)
add_executable(maze src/maze.cpp)
add_executable(main_linked src/main_linked.cpp)
add_executable(main src/main.cpp)

add_executable(tester src/tester.cpp)
