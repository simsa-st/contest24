# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_SOURCE_DIR = /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/SFGUI-Test.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/SFGUI-Test.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/SFGUI-Test.dir/flags.make

examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.o: examples/CMakeFiles/SFGUI-Test.dir/flags.make
examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.o: ../examples/Test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.o"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/SFGUI-Test.dir/Test.cpp.o -c /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples/Test.cpp

examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SFGUI-Test.dir/Test.cpp.i"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples/Test.cpp > CMakeFiles/SFGUI-Test.dir/Test.cpp.i

examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SFGUI-Test.dir/Test.cpp.s"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples/Test.cpp -o CMakeFiles/SFGUI-Test.dir/Test.cpp.s

examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.o.requires:
.PHONY : examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.o.requires

examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.o.provides: examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/SFGUI-Test.dir/build.make examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.o.provides.build
.PHONY : examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.o.provides

examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.o.provides.build: examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.o

# Object files for target SFGUI-Test
SFGUI__Test_OBJECTS = \
"CMakeFiles/SFGUI-Test.dir/Test.cpp.o"

# External object files for target SFGUI-Test
SFGUI__Test_EXTERNAL_OBJECTS =

examples/SFGUI-Test: examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.o
examples/SFGUI-Test: examples/CMakeFiles/SFGUI-Test.dir/build.make
examples/SFGUI-Test: lib/libsfgui.so
examples/SFGUI-Test: /usr/local/lib/libsfml-graphics.so
examples/SFGUI-Test: /usr/local/lib/libsfml-window.so
examples/SFGUI-Test: /usr/local/lib/libsfml-system.so
examples/SFGUI-Test: /usr/lib/x86_64-linux-gnu/libGL.so
examples/SFGUI-Test: /usr/lib/x86_64-linux-gnu/libSM.so
examples/SFGUI-Test: /usr/lib/x86_64-linux-gnu/libICE.so
examples/SFGUI-Test: /usr/lib/x86_64-linux-gnu/libX11.so
examples/SFGUI-Test: /usr/lib/x86_64-linux-gnu/libXext.so
examples/SFGUI-Test: examples/CMakeFiles/SFGUI-Test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable SFGUI-Test"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SFGUI-Test.dir/link.txt --verbose=$(VERBOSE)
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && /usr/bin/cmake -E copy_directory /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples/data /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples/data

# Rule to build all files generated by this target.
examples/CMakeFiles/SFGUI-Test.dir/build: examples/SFGUI-Test
.PHONY : examples/CMakeFiles/SFGUI-Test.dir/build

examples/CMakeFiles/SFGUI-Test.dir/requires: examples/CMakeFiles/SFGUI-Test.dir/Test.cpp.o.requires
.PHONY : examples/CMakeFiles/SFGUI-Test.dir/requires

examples/CMakeFiles/SFGUI-Test.dir/clean:
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/SFGUI-Test.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/SFGUI-Test.dir/clean

examples/CMakeFiles/SFGUI-Test.dir/depend:
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0 /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples/CMakeFiles/SFGUI-Test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/SFGUI-Test.dir/depend

