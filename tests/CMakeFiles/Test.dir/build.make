# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project

# Include any dependencies generated for this target.
include tests/CMakeFiles/Test.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/Test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/Test.dir/flags.make

tests/CMakeFiles/Test.dir/testing.cpp.o: tests/CMakeFiles/Test.dir/flags.make
tests/CMakeFiles/Test.dir/testing.cpp.o: tests/testing.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/Test.dir/testing.cpp.o"
	cd /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Test.dir/testing.cpp.o -c /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project/tests/testing.cpp

tests/CMakeFiles/Test.dir/testing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Test.dir/testing.cpp.i"
	cd /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project/tests/testing.cpp > CMakeFiles/Test.dir/testing.cpp.i

tests/CMakeFiles/Test.dir/testing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Test.dir/testing.cpp.s"
	cd /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project/tests/testing.cpp -o CMakeFiles/Test.dir/testing.cpp.s

# Object files for target Test
Test_OBJECTS = \
"CMakeFiles/Test.dir/testing.cpp.o"

# External object files for target Test
Test_EXTERNAL_OBJECTS =

exe/Test: tests/CMakeFiles/Test.dir/testing.cpp.o
exe/Test: tests/CMakeFiles/Test.dir/build.make
exe/Test: /usr/lib/x86_64-linux-gnu/libgtest.a
exe/Test: /usr/lib/x86_64-linux-gnu/libgmock.a
exe/Test: SFML-2.5.1_for_linux/lib/libsfml-graphics.so.2.5.1
exe/Test: SFML-2.5.1_for_linux/lib/libsfml-window.so.2.5.1
exe/Test: SFML-2.5.1_for_linux/lib/libsfml-system.so.2.5.1
exe/Test: /usr/lib/x86_64-linux-gnu/libgtest.a
exe/Test: tests/CMakeFiles/Test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../exe/Test"
	cd /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/Test.dir/build: exe/Test

.PHONY : tests/CMakeFiles/Test.dir/build

tests/CMakeFiles/Test.dir/clean:
	cd /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project/tests && $(CMAKE_COMMAND) -P CMakeFiles/Test.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/Test.dir/clean

tests/CMakeFiles/Test.dir/depend:
	cd /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project/tests /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project/tests /mnt/c/Users/Alexandr/Desktop/Klinok/TP_2023_Project/tests/CMakeFiles/Test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/Test.dir/depend
