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
CMAKE_SOURCE_DIR = /home/billing/freeDiameter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/billing/freeDiameter/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/testfifo.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/testfifo.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/testfifo.dir/flags.make

tests/CMakeFiles/testfifo.dir/testfifo.c.o: tests/CMakeFiles/testfifo.dir/flags.make
tests/CMakeFiles/testfifo.dir/testfifo.c.o: ../tests/testfifo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/testfifo.dir/testfifo.c.o"
	cd /home/billing/freeDiameter/build/tests && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/testfifo.dir/testfifo.c.o   -c /home/billing/freeDiameter/tests/testfifo.c

tests/CMakeFiles/testfifo.dir/testfifo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testfifo.dir/testfifo.c.i"
	cd /home/billing/freeDiameter/build/tests && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/billing/freeDiameter/tests/testfifo.c > CMakeFiles/testfifo.dir/testfifo.c.i

tests/CMakeFiles/testfifo.dir/testfifo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testfifo.dir/testfifo.c.s"
	cd /home/billing/freeDiameter/build/tests && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/billing/freeDiameter/tests/testfifo.c -o CMakeFiles/testfifo.dir/testfifo.c.s

# Object files for target testfifo
testfifo_OBJECTS = \
"CMakeFiles/testfifo.dir/testfifo.c.o"

# External object files for target testfifo
testfifo_EXTERNAL_OBJECTS =

tests/testfifo: tests/CMakeFiles/testfifo.dir/testfifo.c.o
tests/testfifo: tests/CMakeFiles/testfifo.dir/build.make
tests/testfifo: libfdcore/libfdcore.so.1.5.0
tests/testfifo: /usr/lib/x86_64-linux-gnu/libgnutls.so
tests/testfifo: /usr/lib/x86_64-linux-gnu/libgcrypt.so
tests/testfifo: libfdproto/libfdproto.so.1.5.0
tests/testfifo: /usr/lib/x86_64-linux-gnu/libidn2.so
tests/testfifo: /usr/lib/x86_64-linux-gnu/libsctp.so
tests/testfifo: /usr/lib/x86_64-linux-gnu/libgnutls.so
tests/testfifo: /usr/lib/x86_64-linux-gnu/libgcrypt.so
tests/testfifo: tests/CMakeFiles/testfifo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable testfifo"
	cd /home/billing/freeDiameter/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testfifo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/testfifo.dir/build: tests/testfifo

.PHONY : tests/CMakeFiles/testfifo.dir/build

tests/CMakeFiles/testfifo.dir/clean:
	cd /home/billing/freeDiameter/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/testfifo.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/testfifo.dir/clean

tests/CMakeFiles/testfifo.dir/depend:
	cd /home/billing/freeDiameter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/billing/freeDiameter /home/billing/freeDiameter/tests /home/billing/freeDiameter/build /home/billing/freeDiameter/build/tests /home/billing/freeDiameter/build/tests/CMakeFiles/testfifo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/testfifo.dir/depend

