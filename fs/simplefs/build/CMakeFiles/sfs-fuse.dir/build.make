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
CMAKE_SOURCE_DIR = /home/guests/190110325/user-land-filesystem/fs/simplefs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/guests/190110325/user-land-filesystem/fs/simplefs/build

# Include any dependencies generated for this target.
include CMakeFiles/sfs-fuse.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sfs-fuse.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sfs-fuse.dir/flags.make

CMakeFiles/sfs-fuse.dir/src/sfs.c.o: CMakeFiles/sfs-fuse.dir/flags.make
CMakeFiles/sfs-fuse.dir/src/sfs.c.o: ../src/sfs.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guests/190110325/user-land-filesystem/fs/simplefs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/sfs-fuse.dir/src/sfs.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sfs-fuse.dir/src/sfs.c.o   -c /home/guests/190110325/user-land-filesystem/fs/simplefs/src/sfs.c

CMakeFiles/sfs-fuse.dir/src/sfs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sfs-fuse.dir/src/sfs.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/guests/190110325/user-land-filesystem/fs/simplefs/src/sfs.c > CMakeFiles/sfs-fuse.dir/src/sfs.c.i

CMakeFiles/sfs-fuse.dir/src/sfs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sfs-fuse.dir/src/sfs.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/guests/190110325/user-land-filesystem/fs/simplefs/src/sfs.c -o CMakeFiles/sfs-fuse.dir/src/sfs.c.s

CMakeFiles/sfs-fuse.dir/src/sfs_debug.c.o: CMakeFiles/sfs-fuse.dir/flags.make
CMakeFiles/sfs-fuse.dir/src/sfs_debug.c.o: ../src/sfs_debug.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guests/190110325/user-land-filesystem/fs/simplefs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/sfs-fuse.dir/src/sfs_debug.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sfs-fuse.dir/src/sfs_debug.c.o   -c /home/guests/190110325/user-land-filesystem/fs/simplefs/src/sfs_debug.c

CMakeFiles/sfs-fuse.dir/src/sfs_debug.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sfs-fuse.dir/src/sfs_debug.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/guests/190110325/user-land-filesystem/fs/simplefs/src/sfs_debug.c > CMakeFiles/sfs-fuse.dir/src/sfs_debug.c.i

CMakeFiles/sfs-fuse.dir/src/sfs_debug.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sfs-fuse.dir/src/sfs_debug.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/guests/190110325/user-land-filesystem/fs/simplefs/src/sfs_debug.c -o CMakeFiles/sfs-fuse.dir/src/sfs_debug.c.s

CMakeFiles/sfs-fuse.dir/src/sfs_utils.c.o: CMakeFiles/sfs-fuse.dir/flags.make
CMakeFiles/sfs-fuse.dir/src/sfs_utils.c.o: ../src/sfs_utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guests/190110325/user-land-filesystem/fs/simplefs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/sfs-fuse.dir/src/sfs_utils.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sfs-fuse.dir/src/sfs_utils.c.o   -c /home/guests/190110325/user-land-filesystem/fs/simplefs/src/sfs_utils.c

CMakeFiles/sfs-fuse.dir/src/sfs_utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sfs-fuse.dir/src/sfs_utils.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/guests/190110325/user-land-filesystem/fs/simplefs/src/sfs_utils.c > CMakeFiles/sfs-fuse.dir/src/sfs_utils.c.i

CMakeFiles/sfs-fuse.dir/src/sfs_utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sfs-fuse.dir/src/sfs_utils.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/guests/190110325/user-land-filesystem/fs/simplefs/src/sfs_utils.c -o CMakeFiles/sfs-fuse.dir/src/sfs_utils.c.s

# Object files for target sfs-fuse
sfs__fuse_OBJECTS = \
"CMakeFiles/sfs-fuse.dir/src/sfs.c.o" \
"CMakeFiles/sfs-fuse.dir/src/sfs_debug.c.o" \
"CMakeFiles/sfs-fuse.dir/src/sfs_utils.c.o"

# External object files for target sfs-fuse
sfs__fuse_EXTERNAL_OBJECTS =

sfs-fuse: CMakeFiles/sfs-fuse.dir/src/sfs.c.o
sfs-fuse: CMakeFiles/sfs-fuse.dir/src/sfs_debug.c.o
sfs-fuse: CMakeFiles/sfs-fuse.dir/src/sfs_utils.c.o
sfs-fuse: CMakeFiles/sfs-fuse.dir/build.make
sfs-fuse: /usr/lib/x86_64-linux-gnu/libfuse.so
sfs-fuse: /home/guests/190110325/lib/libddriver.a
sfs-fuse: CMakeFiles/sfs-fuse.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/guests/190110325/user-land-filesystem/fs/simplefs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable sfs-fuse"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sfs-fuse.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sfs-fuse.dir/build: sfs-fuse

.PHONY : CMakeFiles/sfs-fuse.dir/build

CMakeFiles/sfs-fuse.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sfs-fuse.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sfs-fuse.dir/clean

CMakeFiles/sfs-fuse.dir/depend:
	cd /home/guests/190110325/user-land-filesystem/fs/simplefs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/guests/190110325/user-land-filesystem/fs/simplefs /home/guests/190110325/user-land-filesystem/fs/simplefs /home/guests/190110325/user-land-filesystem/fs/simplefs/build /home/guests/190110325/user-land-filesystem/fs/simplefs/build /home/guests/190110325/user-land-filesystem/fs/simplefs/build/CMakeFiles/sfs-fuse.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sfs-fuse.dir/depend

