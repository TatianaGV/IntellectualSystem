# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mirror_white/CLionProjects/lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mirror_white/CLionProjects/lab1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/back.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/back.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/back.dir/flags.make

CMakeFiles/back.dir/backSearch.cpp.o: CMakeFiles/back.dir/flags.make
CMakeFiles/back.dir/backSearch.cpp.o: ../backSearch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mirror_white/CLionProjects/lab1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/back.dir/backSearch.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/back.dir/backSearch.cpp.o -c /Users/mirror_white/CLionProjects/lab1/backSearch.cpp

CMakeFiles/back.dir/backSearch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/back.dir/backSearch.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mirror_white/CLionProjects/lab1/backSearch.cpp > CMakeFiles/back.dir/backSearch.cpp.i

CMakeFiles/back.dir/backSearch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/back.dir/backSearch.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mirror_white/CLionProjects/lab1/backSearch.cpp -o CMakeFiles/back.dir/backSearch.cpp.s

# Object files for target back
back_OBJECTS = \
"CMakeFiles/back.dir/backSearch.cpp.o"

# External object files for target back
back_EXTERNAL_OBJECTS =

back: CMakeFiles/back.dir/backSearch.cpp.o
back: CMakeFiles/back.dir/build.make
back: CMakeFiles/back.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mirror_white/CLionProjects/lab1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable back"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/back.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/back.dir/build: back

.PHONY : CMakeFiles/back.dir/build

CMakeFiles/back.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/back.dir/cmake_clean.cmake
.PHONY : CMakeFiles/back.dir/clean

CMakeFiles/back.dir/depend:
	cd /Users/mirror_white/CLionProjects/lab1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mirror_white/CLionProjects/lab1 /Users/mirror_white/CLionProjects/lab1 /Users/mirror_white/CLionProjects/lab1/cmake-build-debug /Users/mirror_white/CLionProjects/lab1/cmake-build-debug /Users/mirror_white/CLionProjects/lab1/cmake-build-debug/CMakeFiles/back.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/back.dir/depend
