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
include CMakeFiles/l.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/l.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/l.dir/flags.make

CMakeFiles/l.dir/bidirectional.cpp.o: CMakeFiles/l.dir/flags.make
CMakeFiles/l.dir/bidirectional.cpp.o: ../bidirectional.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mirror_white/CLionProjects/lab1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/l.dir/bidirectional.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/l.dir/bidirectional.cpp.o -c /Users/mirror_white/CLionProjects/lab1/bidirectional.cpp

CMakeFiles/l.dir/bidirectional.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/l.dir/bidirectional.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mirror_white/CLionProjects/lab1/bidirectional.cpp > CMakeFiles/l.dir/bidirectional.cpp.i

CMakeFiles/l.dir/bidirectional.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/l.dir/bidirectional.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mirror_white/CLionProjects/lab1/bidirectional.cpp -o CMakeFiles/l.dir/bidirectional.cpp.s

# Object files for target l
l_OBJECTS = \
"CMakeFiles/l.dir/bidirectional.cpp.o"

# External object files for target l
l_EXTERNAL_OBJECTS =

l : CMakeFiles/l.dir/bidirectional.cpp.o
l : CMakeFiles/l.dir/build.make
l : CMakeFiles/l.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mirror_white/CLionProjects/lab1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable l"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/l.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/l.dir/build: l

.PHONY : CMakeFiles/l.dir/build

CMakeFiles/l.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/l.dir/cmake_clean.cmake
.PHONY : CMakeFiles/l.dir/clean

CMakeFiles/l.dir/depend:
	cd /Users/mirror_white/CLionProjects/lab1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mirror_white/CLionProjects/lab1 /Users/mirror_white/CLionProjects/lab1 /Users/mirror_white/CLionProjects/lab1/cmake-build-debug /Users/mirror_white/CLionProjects/lab1/cmake-build-debug /Users/mirror_white/CLionProjects/lab1/cmake-build-debug/CMakeFiles/l.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/l.dir/depend

