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
CMAKE_SOURCE_DIR = /home/guests/190110325/user-land-filesystem/fs/samples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/guests/190110325/user-land-filesystem/fs/samples

# Include any dependencies generated for this target.
include CMakeFiles/mfs-fuse.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mfs-fuse.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mfs-fuse.dir/flags.make

CMakeFiles/mfs-fuse.dir/src/bitmap.c.o: CMakeFiles/mfs-fuse.dir/flags.make
CMakeFiles/mfs-fuse.dir/src/bitmap.c.o: src/bitmap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guests/190110325/user-land-filesystem/fs/samples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mfs-fuse.dir/src/bitmap.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mfs-fuse.dir/src/bitmap.c.o   -c /home/guests/190110325/user-land-filesystem/fs/samples/src/bitmap.c

CMakeFiles/mfs-fuse.dir/src/bitmap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mfs-fuse.dir/src/bitmap.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/guests/190110325/user-land-filesystem/fs/samples/src/bitmap.c > CMakeFiles/mfs-fuse.dir/src/bitmap.c.i

CMakeFiles/mfs-fuse.dir/src/bitmap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mfs-fuse.dir/src/bitmap.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/guests/190110325/user-land-filesystem/fs/samples/src/bitmap.c -o CMakeFiles/mfs-fuse.dir/src/bitmap.c.s

CMakeFiles/mfs-fuse.dir/src/fsdisk.c.o: CMakeFiles/mfs-fuse.dir/flags.make
CMakeFiles/mfs-fuse.dir/src/fsdisk.c.o: src/fsdisk.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guests/190110325/user-land-filesystem/fs/samples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/mfs-fuse.dir/src/fsdisk.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mfs-fuse.dir/src/fsdisk.c.o   -c /home/guests/190110325/user-land-filesystem/fs/samples/src/fsdisk.c

CMakeFiles/mfs-fuse.dir/src/fsdisk.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mfs-fuse.dir/src/fsdisk.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/guests/190110325/user-land-filesystem/fs/samples/src/fsdisk.c > CMakeFiles/mfs-fuse.dir/src/fsdisk.c.i

CMakeFiles/mfs-fuse.dir/src/fsdisk.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mfs-fuse.dir/src/fsdisk.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/guests/190110325/user-land-filesystem/fs/samples/src/fsdisk.c -o CMakeFiles/mfs-fuse.dir/src/fsdisk.c.s

CMakeFiles/mfs-fuse.dir/src/fsmain.c.o: CMakeFiles/mfs-fuse.dir/flags.make
CMakeFiles/mfs-fuse.dir/src/fsmain.c.o: src/fsmain.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guests/190110325/user-land-filesystem/fs/samples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/mfs-fuse.dir/src/fsmain.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mfs-fuse.dir/src/fsmain.c.o   -c /home/guests/190110325/user-land-filesystem/fs/samples/src/fsmain.c

CMakeFiles/mfs-fuse.dir/src/fsmain.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mfs-fuse.dir/src/fsmain.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/guests/190110325/user-land-filesystem/fs/samples/src/fsmain.c > CMakeFiles/mfs-fuse.dir/src/fsmain.c.i

CMakeFiles/mfs-fuse.dir/src/fsmain.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mfs-fuse.dir/src/fsmain.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/guests/190110325/user-land-filesystem/fs/samples/src/fsmain.c -o CMakeFiles/mfs-fuse.dir/src/fsmain.c.s

CMakeFiles/mfs-fuse.dir/src/fsoperations.c.o: CMakeFiles/mfs-fuse.dir/flags.make
CMakeFiles/mfs-fuse.dir/src/fsoperations.c.o: src/fsoperations.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guests/190110325/user-land-filesystem/fs/samples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/mfs-fuse.dir/src/fsoperations.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mfs-fuse.dir/src/fsoperations.c.o   -c /home/guests/190110325/user-land-filesystem/fs/samples/src/fsoperations.c

CMakeFiles/mfs-fuse.dir/src/fsoperations.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mfs-fuse.dir/src/fsoperations.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/guests/190110325/user-land-filesystem/fs/samples/src/fsoperations.c > CMakeFiles/mfs-fuse.dir/src/fsoperations.c.i

CMakeFiles/mfs-fuse.dir/src/fsoperations.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mfs-fuse.dir/src/fsoperations.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/guests/190110325/user-land-filesystem/fs/samples/src/fsoperations.c -o CMakeFiles/mfs-fuse.dir/src/fsoperations.c.s

CMakeFiles/mfs-fuse.dir/src/fstree.c.o: CMakeFiles/mfs-fuse.dir/flags.make
CMakeFiles/mfs-fuse.dir/src/fstree.c.o: src/fstree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guests/190110325/user-land-filesystem/fs/samples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/mfs-fuse.dir/src/fstree.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mfs-fuse.dir/src/fstree.c.o   -c /home/guests/190110325/user-land-filesystem/fs/samples/src/fstree.c

CMakeFiles/mfs-fuse.dir/src/fstree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mfs-fuse.dir/src/fstree.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/guests/190110325/user-land-filesystem/fs/samples/src/fstree.c > CMakeFiles/mfs-fuse.dir/src/fstree.c.i

CMakeFiles/mfs-fuse.dir/src/fstree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mfs-fuse.dir/src/fstree.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/guests/190110325/user-land-filesystem/fs/samples/src/fstree.c -o CMakeFiles/mfs-fuse.dir/src/fstree.c.s

# Object files for target mfs-fuse
mfs__fuse_OBJECTS = \
"CMakeFiles/mfs-fuse.dir/src/bitmap.c.o" \
"CMakeFiles/mfs-fuse.dir/src/fsdisk.c.o" \
"CMakeFiles/mfs-fuse.dir/src/fsmain.c.o" \
"CMakeFiles/mfs-fuse.dir/src/fsoperations.c.o" \
"CMakeFiles/mfs-fuse.dir/src/fstree.c.o"

# External object files for target mfs-fuse
mfs__fuse_EXTERNAL_OBJECTS =

mfs-fuse: CMakeFiles/mfs-fuse.dir/src/bitmap.c.o
mfs-fuse: CMakeFiles/mfs-fuse.dir/src/fsdisk.c.o
mfs-fuse: CMakeFiles/mfs-fuse.dir/src/fsmain.c.o
mfs-fuse: CMakeFiles/mfs-fuse.dir/src/fsoperations.c.o
mfs-fuse: CMakeFiles/mfs-fuse.dir/src/fstree.c.o
mfs-fuse: CMakeFiles/mfs-fuse.dir/build.make
mfs-fuse: /usr/lib/x86_64-linux-gnu/libfuse.so
mfs-fuse: CMakeFiles/mfs-fuse.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/guests/190110325/user-land-filesystem/fs/samples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable mfs-fuse"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mfs-fuse.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mfs-fuse.dir/build: mfs-fuse

.PHONY : CMakeFiles/mfs-fuse.dir/build

CMakeFiles/mfs-fuse.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mfs-fuse.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mfs-fuse.dir/clean

CMakeFiles/mfs-fuse.dir/depend:
	cd /home/guests/190110325/user-land-filesystem/fs/samples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/guests/190110325/user-land-filesystem/fs/samples /home/guests/190110325/user-land-filesystem/fs/samples /home/guests/190110325/user-land-filesystem/fs/samples /home/guests/190110325/user-land-filesystem/fs/samples /home/guests/190110325/user-land-filesystem/fs/samples/CMakeFiles/mfs-fuse.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mfs-fuse.dir/depend
