cmake_minimum_required(VERSION 3.9)
project(lab2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.13.0/lib/cmake")

add_executable(lab2 fifteens.cpp Node.h Search_algs.h Search_algs.cpp Heuristics.h Heuristics.cpp)

find_package(Qt5Core REQUIRED)
target_link_libraries(lab2 Qt5::Core)