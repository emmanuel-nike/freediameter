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
include extensions/acl_wl/CMakeFiles/acl_wl.dir/depend.make

# Include the progress variables for this target.
include extensions/acl_wl/CMakeFiles/acl_wl.dir/progress.make

# Include the compile flags for this target's objects.
include extensions/acl_wl/CMakeFiles/acl_wl.dir/flags.make

extensions/acl_wl/lex.aw_conf.c: ../extensions/acl_wl/aw_conf.l
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating lex.aw_conf.c"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && /usr/bin/flex -Paw_conf -o/home/billing/freeDiameter/build/extensions/acl_wl/lex.aw_conf.c /home/billing/freeDiameter/extensions/acl_wl/aw_conf.l

extensions/acl_wl/aw_conf.tab.c: ../extensions/acl_wl/aw_conf.y
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating aw_conf.tab.c, aw_conf.tab.h"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && /usr/bin/bison --name-prefix=aw_conf --defines --output-file=/home/billing/freeDiameter/build/extensions/acl_wl/aw_conf.tab.c /home/billing/freeDiameter/extensions/acl_wl/aw_conf.y

extensions/acl_wl/aw_conf.tab.h: extensions/acl_wl/aw_conf.tab.c
	@$(CMAKE_COMMAND) -E touch_nocreate extensions/acl_wl/aw_conf.tab.h

extensions/acl_wl/CMakeFiles/acl_wl.dir/acl_wl.c.o: extensions/acl_wl/CMakeFiles/acl_wl.dir/flags.make
extensions/acl_wl/CMakeFiles/acl_wl.dir/acl_wl.c.o: ../extensions/acl_wl/acl_wl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object extensions/acl_wl/CMakeFiles/acl_wl.dir/acl_wl.c.o"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/acl_wl.dir/acl_wl.c.o   -c /home/billing/freeDiameter/extensions/acl_wl/acl_wl.c

extensions/acl_wl/CMakeFiles/acl_wl.dir/acl_wl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/acl_wl.dir/acl_wl.c.i"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/billing/freeDiameter/extensions/acl_wl/acl_wl.c > CMakeFiles/acl_wl.dir/acl_wl.c.i

extensions/acl_wl/CMakeFiles/acl_wl.dir/acl_wl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/acl_wl.dir/acl_wl.c.s"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/billing/freeDiameter/extensions/acl_wl/acl_wl.c -o CMakeFiles/acl_wl.dir/acl_wl.c.s

extensions/acl_wl/CMakeFiles/acl_wl.dir/aw_tree.c.o: extensions/acl_wl/CMakeFiles/acl_wl.dir/flags.make
extensions/acl_wl/CMakeFiles/acl_wl.dir/aw_tree.c.o: ../extensions/acl_wl/aw_tree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object extensions/acl_wl/CMakeFiles/acl_wl.dir/aw_tree.c.o"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/acl_wl.dir/aw_tree.c.o   -c /home/billing/freeDiameter/extensions/acl_wl/aw_tree.c

extensions/acl_wl/CMakeFiles/acl_wl.dir/aw_tree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/acl_wl.dir/aw_tree.c.i"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/billing/freeDiameter/extensions/acl_wl/aw_tree.c > CMakeFiles/acl_wl.dir/aw_tree.c.i

extensions/acl_wl/CMakeFiles/acl_wl.dir/aw_tree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/acl_wl.dir/aw_tree.c.s"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/billing/freeDiameter/extensions/acl_wl/aw_tree.c -o CMakeFiles/acl_wl.dir/aw_tree.c.s

extensions/acl_wl/CMakeFiles/acl_wl.dir/lex.aw_conf.c.o: extensions/acl_wl/CMakeFiles/acl_wl.dir/flags.make
extensions/acl_wl/CMakeFiles/acl_wl.dir/lex.aw_conf.c.o: extensions/acl_wl/lex.aw_conf.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object extensions/acl_wl/CMakeFiles/acl_wl.dir/lex.aw_conf.c.o"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -I /home/billing/freeDiameter/extensions/acl_wl -o CMakeFiles/acl_wl.dir/lex.aw_conf.c.o   -c /home/billing/freeDiameter/build/extensions/acl_wl/lex.aw_conf.c

extensions/acl_wl/CMakeFiles/acl_wl.dir/lex.aw_conf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/acl_wl.dir/lex.aw_conf.c.i"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -I /home/billing/freeDiameter/extensions/acl_wl -E /home/billing/freeDiameter/build/extensions/acl_wl/lex.aw_conf.c > CMakeFiles/acl_wl.dir/lex.aw_conf.c.i

extensions/acl_wl/CMakeFiles/acl_wl.dir/lex.aw_conf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/acl_wl.dir/lex.aw_conf.c.s"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -I /home/billing/freeDiameter/extensions/acl_wl -S /home/billing/freeDiameter/build/extensions/acl_wl/lex.aw_conf.c -o CMakeFiles/acl_wl.dir/lex.aw_conf.c.s

extensions/acl_wl/CMakeFiles/acl_wl.dir/aw_conf.tab.c.o: extensions/acl_wl/CMakeFiles/acl_wl.dir/flags.make
extensions/acl_wl/CMakeFiles/acl_wl.dir/aw_conf.tab.c.o: extensions/acl_wl/aw_conf.tab.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object extensions/acl_wl/CMakeFiles/acl_wl.dir/aw_conf.tab.c.o"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -I /home/billing/freeDiameter/extensions/acl_wl -o CMakeFiles/acl_wl.dir/aw_conf.tab.c.o   -c /home/billing/freeDiameter/build/extensions/acl_wl/aw_conf.tab.c

extensions/acl_wl/CMakeFiles/acl_wl.dir/aw_conf.tab.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/acl_wl.dir/aw_conf.tab.c.i"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -I /home/billing/freeDiameter/extensions/acl_wl -E /home/billing/freeDiameter/build/extensions/acl_wl/aw_conf.tab.c > CMakeFiles/acl_wl.dir/aw_conf.tab.c.i

extensions/acl_wl/CMakeFiles/acl_wl.dir/aw_conf.tab.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/acl_wl.dir/aw_conf.tab.c.s"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -I /home/billing/freeDiameter/extensions/acl_wl -S /home/billing/freeDiameter/build/extensions/acl_wl/aw_conf.tab.c -o CMakeFiles/acl_wl.dir/aw_conf.tab.c.s

# Object files for target acl_wl
acl_wl_OBJECTS = \
"CMakeFiles/acl_wl.dir/acl_wl.c.o" \
"CMakeFiles/acl_wl.dir/aw_tree.c.o" \
"CMakeFiles/acl_wl.dir/lex.aw_conf.c.o" \
"CMakeFiles/acl_wl.dir/aw_conf.tab.c.o"

# External object files for target acl_wl
acl_wl_EXTERNAL_OBJECTS =

extensions/acl_wl.fdx: extensions/acl_wl/CMakeFiles/acl_wl.dir/acl_wl.c.o
extensions/acl_wl.fdx: extensions/acl_wl/CMakeFiles/acl_wl.dir/aw_tree.c.o
extensions/acl_wl.fdx: extensions/acl_wl/CMakeFiles/acl_wl.dir/lex.aw_conf.c.o
extensions/acl_wl.fdx: extensions/acl_wl/CMakeFiles/acl_wl.dir/aw_conf.tab.c.o
extensions/acl_wl.fdx: extensions/acl_wl/CMakeFiles/acl_wl.dir/build.make
extensions/acl_wl.fdx: extensions/acl_wl/CMakeFiles/acl_wl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C shared module ../acl_wl.fdx"
	cd /home/billing/freeDiameter/build/extensions/acl_wl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/acl_wl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extensions/acl_wl/CMakeFiles/acl_wl.dir/build: extensions/acl_wl.fdx

.PHONY : extensions/acl_wl/CMakeFiles/acl_wl.dir/build

extensions/acl_wl/CMakeFiles/acl_wl.dir/clean:
	cd /home/billing/freeDiameter/build/extensions/acl_wl && $(CMAKE_COMMAND) -P CMakeFiles/acl_wl.dir/cmake_clean.cmake
.PHONY : extensions/acl_wl/CMakeFiles/acl_wl.dir/clean

extensions/acl_wl/CMakeFiles/acl_wl.dir/depend: extensions/acl_wl/lex.aw_conf.c
extensions/acl_wl/CMakeFiles/acl_wl.dir/depend: extensions/acl_wl/aw_conf.tab.c
extensions/acl_wl/CMakeFiles/acl_wl.dir/depend: extensions/acl_wl/aw_conf.tab.h
	cd /home/billing/freeDiameter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/billing/freeDiameter /home/billing/freeDiameter/extensions/acl_wl /home/billing/freeDiameter/build /home/billing/freeDiameter/build/extensions/acl_wl /home/billing/freeDiameter/build/extensions/acl_wl/CMakeFiles/acl_wl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extensions/acl_wl/CMakeFiles/acl_wl.dir/depend

