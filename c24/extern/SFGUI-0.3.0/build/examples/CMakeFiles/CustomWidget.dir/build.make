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
include examples/CMakeFiles/CustomWidget.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/CustomWidget.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/CustomWidget.dir/flags.make

examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o: examples/CMakeFiles/CustomWidget.dir/flags.make
examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o: ../examples/CustomWidget.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o -c /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples/CustomWidget.cpp

examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CustomWidget.dir/CustomWidget.cpp.i"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples/CustomWidget.cpp > CMakeFiles/CustomWidget.dir/CustomWidget.cpp.i

examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CustomWidget.dir/CustomWidget.cpp.s"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples/CustomWidget.cpp -o CMakeFiles/CustomWidget.dir/CustomWidget.cpp.s

examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.requires:
.PHONY : examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.requires

examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.provides: examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/CustomWidget.dir/build.make examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.provides.build
.PHONY : examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.provides

examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.provides.build: examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o

# Object files for target CustomWidget
CustomWidget_OBJECTS = \
"CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o"

# External object files for target CustomWidget
CustomWidget_EXTERNAL_OBJECTS =

examples/CustomWidget: examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o
examples/CustomWidget: examples/CMakeFiles/CustomWidget.dir/build.make
examples/CustomWidget: lib/libsfgui.so
examples/CustomWidget: /usr/local/lib/libsfml-graphics.so
examples/CustomWidget: /usr/local/lib/libsfml-window.so
examples/CustomWidget: /usr/local/lib/libsfml-system.so
examples/CustomWidget: /usr/lib/x86_64-linux-gnu/libGL.so
examples/CustomWidget: /usr/lib/x86_64-linux-gnu/libSM.so
examples/CustomWidget: /usr/lib/x86_64-linux-gnu/libICE.so
examples/CustomWidget: /usr/lib/x86_64-linux-gnu/libX11.so
examples/CustomWidget: /usr/lib/x86_64-linux-gnu/libXext.so
examples/CustomWidget: examples/CMakeFiles/CustomWidget.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable CustomWidget"
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CustomWidget.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/CustomWidget.dir/build: examples/CustomWidget
.PHONY : examples/CMakeFiles/CustomWidget.dir/build

examples/CMakeFiles/CustomWidget.dir/requires: examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.requires
.PHONY : examples/CMakeFiles/CustomWidget.dir/requires

examples/CMakeFiles/CustomWidget.dir/clean:
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/CustomWidget.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/CustomWidget.dir/clean

examples/CMakeFiles/CustomWidget.dir/depend:
	cd /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0 /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/examples /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples /home/gorli/projects/contest24/c24/extern/SFGUI-0.3.0/build/examples/CMakeFiles/CustomWidget.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/CustomWidget.dir/depend

