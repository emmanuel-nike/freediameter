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
include extensions/dict_sip/CMakeFiles/dict_sip.dir/depend.make

# Include the progress variables for this target.
include extensions/dict_sip/CMakeFiles/dict_sip.dir/progress.make

# Include the compile flags for this target's objects.
include extensions/dict_sip/CMakeFiles/dict_sip.dir/flags.make

extensions/dict_sip/CMakeFiles/dict_sip.dir/dict_sip.c.o: extensions/dict_sip/CMakeFiles/dict_sip.dir/flags.make
extensions/dict_sip/CMakeFiles/dict_sip.dir/dict_sip.c.o: ../extensions/dict_sip/dict_sip.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object extensions/dict_sip/CMakeFiles/dict_sip.dir/dict_sip.c.o"
	cd /home/billing/freeDiameter/build/extensions/dict_sip && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dict_sip.dir/dict_sip.c.o   -c /home/billing/freeDiameter/extensions/dict_sip/dict_sip.c

extensions/dict_sip/CMakeFiles/dict_sip.dir/dict_sip.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dict_sip.dir/dict_sip.c.i"
	cd /home/billing/freeDiameter/build/extensions/dict_sip && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/billing/freeDiameter/extensions/dict_sip/dict_sip.c > CMakeFiles/dict_sip.dir/dict_sip.c.i

extensions/dict_sip/CMakeFiles/dict_sip.dir/dict_sip.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dict_sip.dir/dict_sip.c.s"
	cd /home/billing/freeDiameter/build/extensions/dict_sip && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/billing/freeDiameter/extensions/dict_sip/dict_sip.c -o CMakeFiles/dict_sip.dir/dict_sip.c.s

# Object files for target dict_sip
dict_sip_OBJECTS = \
"CMakeFiles/dict_sip.dir/dict_sip.c.o"

# External object files for target dict_sip
dict_sip_EXTERNAL_OBJECTS =

extensions/dict_sip.fdx: extensions/dict_sip/CMakeFiles/dict_sip.dir/dict_sip.c.o
extensions/dict_sip.fdx: extensions/dict_sip/CMakeFiles/dict_sip.dir/build.make
extensions/dict_sip.fdx: extensions/dict_sip/CMakeFiles/dict_sip.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared module ../dict_sip.fdx"
	cd /home/billing/freeDiameter/build/extensions/dict_sip && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dict_sip.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extensions/dict_sip/CMakeFiles/dict_sip.dir/build: extensions/dict_sip.fdx

.PHONY : extensions/dict_sip/CMakeFiles/dict_sip.dir/build

extensions/dict_sip/CMakeFiles/dict_sip.dir/clean:
	cd /home/billing/freeDiameter/build/extensions/dict_sip && $(CMAKE_COMMAND) -P CMakeFiles/dict_sip.dir/cmake_clean.cmake
.PHONY : extensions/dict_sip/CMakeFiles/dict_sip.dir/clean

extensions/dict_sip/CMakeFiles/dict_sip.dir/depend:
	cd /home/billing/freeDiameter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/billing/freeDiameter /home/billing/freeDiameter/extensions/dict_sip /home/billing/freeDiameter/build /home/billing/freeDiameter/build/extensions/dict_sip /home/billing/freeDiameter/build/extensions/dict_sip/CMakeFiles/dict_sip.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extensions/dict_sip/CMakeFiles/dict_sip.dir/depend

