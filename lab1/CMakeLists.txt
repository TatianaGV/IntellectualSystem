cmake_minimum_required(VERSION 3.14)
project(lab1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.13.0/lib/cmake")


set(SOURCE_FILES main.cpp tree_search.h)
add_executable(lab1 ${SOURCE_FILES})

set(SOURCE_FILES tree_search.h backSearch.cpp )
add_executable(backSearch ${SOURCE_FILES})

set(SOURCE_FILES bidirectional.cpp)
add_executable(bidirect ${SOURCE_FILES})

find_package(Qt5Core REQUIRED)
target_link_libraries(lab1 Qt5::Core)
target_link_libraries(backSearch Qt5::Core)
target_link_libraries(bidirect Qt5::Core)