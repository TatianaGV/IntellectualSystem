cmake_minimum_required(VERSION 3.9)
project(lab3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.13.0/lib/cmake")

add_executable(lab3 main.cpp Ugolki.h gameBorder.h algoritmIDS.h)

find_package(Qt5Core REQUIRED)
target_link_libraries(lab3 Qt5::Core)