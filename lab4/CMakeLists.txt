cmake_minimum_required(VERSION 3.14)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.13.0/lib/cmake")

add_executable(untitled main.cpp Ugolki.h border.h)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)

target_link_libraries(untitled Qt5::Widgets)

target_link_libraries(untitled Qt5::Core)
target_link_libraries(untitled Qt5::Widgets)
target_link_libraries(untitled Qt5::Quick)