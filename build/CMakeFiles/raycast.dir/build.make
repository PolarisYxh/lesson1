# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/yxh/homework/glraycasting

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yxh/homework/glraycasting/build

# Include any dependencies generated for this target.
include CMakeFiles/raycast.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/raycast.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raycast.dir/flags.make

CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o: CMakeFiles/raycast.dir/flags.make
CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o: ../src/coordinate_systems_multiple.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yxh/homework/glraycasting/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o -c /home/yxh/homework/glraycasting/src/coordinate_systems_multiple.cpp

CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yxh/homework/glraycasting/src/coordinate_systems_multiple.cpp > CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.i

CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yxh/homework/glraycasting/src/coordinate_systems_multiple.cpp -o CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.s

CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o.requires:

.PHONY : CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o.requires

CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o.provides: CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o.requires
	$(MAKE) -f CMakeFiles/raycast.dir/build.make CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o.provides.build
.PHONY : CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o.provides

CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o.provides.build: CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o


# Object files for target raycast
raycast_OBJECTS = \
"CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o"

# External object files for target raycast
raycast_EXTERNAL_OBJECTS =

raycast: CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o
raycast: CMakeFiles/raycast.dir/build.make
raycast: /usr/lib/x86_64-linux-gnu/libglfw.so
raycast: libSTB_IMAGE.a
raycast: libGLAD.a
raycast: CMakeFiles/raycast.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yxh/homework/glraycasting/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable raycast"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raycast.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raycast.dir/build: raycast

.PHONY : CMakeFiles/raycast.dir/build

CMakeFiles/raycast.dir/requires: CMakeFiles/raycast.dir/src/coordinate_systems_multiple.cpp.o.requires

.PHONY : CMakeFiles/raycast.dir/requires

CMakeFiles/raycast.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/raycast.dir/cmake_clean.cmake
.PHONY : CMakeFiles/raycast.dir/clean

CMakeFiles/raycast.dir/depend:
	cd /home/yxh/homework/glraycasting/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yxh/homework/glraycasting /home/yxh/homework/glraycasting /home/yxh/homework/glraycasting/build /home/yxh/homework/glraycasting/build /home/yxh/homework/glraycasting/build/CMakeFiles/raycast.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/raycast.dir/depend
