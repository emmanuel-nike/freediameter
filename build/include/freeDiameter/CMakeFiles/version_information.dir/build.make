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

# Utility rule file for version_information.

# Include the progress variables for this target.
include include/freeDiameter/CMakeFiles/version_information.dir/progress.make

include/freeDiameter/CMakeFiles/version_information: ../.hg/dirstate
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Retrieving version of the hg repository"
	cd /home/billing/freeDiameter && /usr/bin/cmake -D HGCOMMAND="/usr/bin/hg" -D SRC="/home/billing/freeDiameter/include/freeDiameter/version.h.in" -D DST="/home/billing/freeDiameter/build/include/freeDiameter/version.h" -P /home/billing/freeDiameter/cmake/Modules/GetVersionWithHg.cmake

version_information: include/freeDiameter/CMakeFiles/version_information
version_information: include/freeDiameter/CMakeFiles/version_information.dir/build.make

.PHONY : version_information

# Rule to build all files generated by this target.
include/freeDiameter/CMakeFiles/version_information.dir/build: version_information

.PHONY : include/freeDiameter/CMakeFiles/version_information.dir/build

include/freeDiameter/CMakeFiles/version_information.dir/clean:
	cd /home/billing/freeDiameter/build/include/freeDiameter && $(CMAKE_COMMAND) -P CMakeFiles/version_information.dir/cmake_clean.cmake
.PHONY : include/freeDiameter/CMakeFiles/version_information.dir/clean

include/freeDiameter/CMakeFiles/version_information.dir/depend:
	cd /home/billing/freeDiameter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/billing/freeDiameter /home/billing/freeDiameter/include/freeDiameter /home/billing/freeDiameter/build /home/billing/freeDiameter/build/include/freeDiameter /home/billing/freeDiameter/build/include/freeDiameter/CMakeFiles/version_information.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/freeDiameter/CMakeFiles/version_information.dir/depend

