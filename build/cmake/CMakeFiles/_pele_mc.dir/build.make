# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/stefano/Work/mcpele

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stefano/Work/mcpele/build/cmake

# Include any dependencies generated for this target.
include CMakeFiles/_pele_mc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/_pele_mc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/_pele_mc.dir/flags.make

CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o: CMakeFiles/_pele_mc.dir/flags.make
CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o: ../../mcpele/monte_carlo/_pele_mc.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/stefano/Work/mcpele/build/cmake/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o -c /home/stefano/Work/mcpele/mcpele/monte_carlo/_pele_mc.cxx

CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/stefano/Work/mcpele/mcpele/monte_carlo/_pele_mc.cxx > CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.i

CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/stefano/Work/mcpele/mcpele/monte_carlo/_pele_mc.cxx -o CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.s

CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o.requires:
.PHONY : CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o.requires

CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o.provides: CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o.requires
	$(MAKE) -f CMakeFiles/_pele_mc.dir/build.make CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o.provides.build
.PHONY : CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o.provides

CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o.provides.build: CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o

# Object files for target _pele_mc
_pele_mc_OBJECTS = \
"CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o"

# External object files for target _pele_mc
_pele_mc_EXTERNAL_OBJECTS =

_pele_mc.so: CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o
_pele_mc.so: CMakeFiles/_pele_mc.dir/build.make
_pele_mc.so: libmcpele_lib.so
_pele_mc.so: CMakeFiles/_pele_mc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library _pele_mc.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_pele_mc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/_pele_mc.dir/build: _pele_mc.so
.PHONY : CMakeFiles/_pele_mc.dir/build

CMakeFiles/_pele_mc.dir/requires: CMakeFiles/_pele_mc.dir/mcpele/monte_carlo/_pele_mc.cxx.o.requires
.PHONY : CMakeFiles/_pele_mc.dir/requires

CMakeFiles/_pele_mc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/_pele_mc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/_pele_mc.dir/clean

CMakeFiles/_pele_mc.dir/depend:
	cd /home/stefano/Work/mcpele/build/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stefano/Work/mcpele /home/stefano/Work/mcpele /home/stefano/Work/mcpele/build/cmake /home/stefano/Work/mcpele/build/cmake /home/stefano/Work/mcpele/build/cmake/CMakeFiles/_pele_mc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/_pele_mc.dir/depend

