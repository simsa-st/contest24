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
include examples/CMakeFiles/GuessMyNumber.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/GuessMyNumber.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/GuessMyNumber.dir/flags.make

examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o: examples/CMakeFiles/GuessMyNumber.dir/flags.make
examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o: ../examples/GuessMyNumber.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o -c /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples/GuessMyNumber.cpp

examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.i"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples/GuessMyNumber.cpp > CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.i

examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.s"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples/GuessMyNumber.cpp -o CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.s

examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o.requires:
.PHONY : examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o.requires

examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o.provides: examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/GuessMyNumber.dir/build.make examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o.provides.build
.PHONY : examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o.provides

examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o.provides.build: examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o

# Object files for target GuessMyNumber
GuessMyNumber_OBJECTS = \
"CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o"

# External object files for target GuessMyNumber
GuessMyNumber_EXTERNAL_OBJECTS =

examples/GuessMyNumber: examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o
examples/GuessMyNumber: examples/CMakeFiles/GuessMyNumber.dir/build.make
examples/GuessMyNumber: lib/libsfgui.so
examples/GuessMyNumber: /usr/local/lib/libsfml-graphics.so
examples/GuessMyNumber: /usr/local/lib/libsfml-window.so
examples/GuessMyNumber: /usr/local/lib/libsfml-system.so
examples/GuessMyNumber: /usr/lib/x86_64-linux-gnu/libGL.so
examples/GuessMyNumber: /usr/lib/x86_64-linux-gnu/libSM.so
examples/GuessMyNumber: /usr/lib/x86_64-linux-gnu/libICE.so
examples/GuessMyNumber: /usr/lib/x86_64-linux-gnu/libX11.so
examples/GuessMyNumber: /usr/lib/x86_64-linux-gnu/libXext.so
examples/GuessMyNumber: examples/CMakeFiles/GuessMyNumber.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable GuessMyNumber"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GuessMyNumber.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/GuessMyNumber.dir/build: examples/GuessMyNumber
.PHONY : examples/CMakeFiles/GuessMyNumber.dir/build

examples/CMakeFiles/GuessMyNumber.dir/requires: examples/CMakeFiles/GuessMyNumber.dir/GuessMyNumber.cpp.o.requires
.PHONY : examples/CMakeFiles/GuessMyNumber.dir/requires

examples/CMakeFiles/GuessMyNumber.dir/clean:
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/GuessMyNumber.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/GuessMyNumber.dir/clean

examples/CMakeFiles/GuessMyNumber.dir/depend:
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0 /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples/CMakeFiles/GuessMyNumber.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/GuessMyNumber.dir/depend

