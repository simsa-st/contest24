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
include examples/CMakeFiles/Entry.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/Entry.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/Entry.dir/flags.make

examples/CMakeFiles/Entry.dir/Entry.cpp.o: examples/CMakeFiles/Entry.dir/flags.make
examples/CMakeFiles/Entry.dir/Entry.cpp.o: ../examples/Entry.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/Entry.dir/Entry.cpp.o"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Entry.dir/Entry.cpp.o -c /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples/Entry.cpp

examples/CMakeFiles/Entry.dir/Entry.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Entry.dir/Entry.cpp.i"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples/Entry.cpp > CMakeFiles/Entry.dir/Entry.cpp.i

examples/CMakeFiles/Entry.dir/Entry.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Entry.dir/Entry.cpp.s"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples/Entry.cpp -o CMakeFiles/Entry.dir/Entry.cpp.s

examples/CMakeFiles/Entry.dir/Entry.cpp.o.requires:
.PHONY : examples/CMakeFiles/Entry.dir/Entry.cpp.o.requires

examples/CMakeFiles/Entry.dir/Entry.cpp.o.provides: examples/CMakeFiles/Entry.dir/Entry.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/Entry.dir/build.make examples/CMakeFiles/Entry.dir/Entry.cpp.o.provides.build
.PHONY : examples/CMakeFiles/Entry.dir/Entry.cpp.o.provides

examples/CMakeFiles/Entry.dir/Entry.cpp.o.provides.build: examples/CMakeFiles/Entry.dir/Entry.cpp.o

# Object files for target Entry
Entry_OBJECTS = \
"CMakeFiles/Entry.dir/Entry.cpp.o"

# External object files for target Entry
Entry_EXTERNAL_OBJECTS =

examples/Entry: examples/CMakeFiles/Entry.dir/Entry.cpp.o
examples/Entry: examples/CMakeFiles/Entry.dir/build.make
examples/Entry: lib/libsfgui.so
examples/Entry: /usr/local/lib/libsfml-graphics.so
examples/Entry: /usr/local/lib/libsfml-window.so
examples/Entry: /usr/local/lib/libsfml-system.so
examples/Entry: /usr/lib/x86_64-linux-gnu/libGL.so
examples/Entry: /usr/lib/x86_64-linux-gnu/libSM.so
examples/Entry: /usr/lib/x86_64-linux-gnu/libICE.so
examples/Entry: /usr/lib/x86_64-linux-gnu/libX11.so
examples/Entry: /usr/lib/x86_64-linux-gnu/libXext.so
examples/Entry: examples/CMakeFiles/Entry.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Entry"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Entry.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/Entry.dir/build: examples/Entry
.PHONY : examples/CMakeFiles/Entry.dir/build

examples/CMakeFiles/Entry.dir/requires: examples/CMakeFiles/Entry.dir/Entry.cpp.o.requires
.PHONY : examples/CMakeFiles/Entry.dir/requires

examples/CMakeFiles/Entry.dir/clean:
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/Entry.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/Entry.dir/clean

examples/CMakeFiles/Entry.dir/depend:
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0 /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples/CMakeFiles/Entry.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/Entry.dir/depend
