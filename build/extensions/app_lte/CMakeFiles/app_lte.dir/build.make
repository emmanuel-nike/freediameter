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
include extensions/app_lte/CMakeFiles/app_lte.dir/depend.make

# Include the progress variables for this target.
include extensions/app_lte/CMakeFiles/app_lte.dir/progress.make

# Include the compile flags for this target's objects.
include extensions/app_lte/CMakeFiles/app_lte.dir/flags.make

extensions/app_lte/lex.app_lte_conf.c: ../extensions/app_lte/app_lte_conf.l
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating lex.app_lte_conf.c"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/flex -Papp_lte_conf -o/home/billing/freeDiameter/build/extensions/app_lte/lex.app_lte_conf.c /home/billing/freeDiameter/extensions/app_lte/app_lte_conf.l

extensions/app_lte/app_lte_conf.tab.c: ../extensions/app_lte/app_lte_conf.y
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating app_lte_conf.tab.c, app_lte_conf.tab.h"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/bison --name-prefix=app_lte_conf --defines --output-file=/home/billing/freeDiameter/build/extensions/app_lte/app_lte_conf.tab.c /home/billing/freeDiameter/extensions/app_lte/app_lte_conf.y

extensions/app_lte/app_lte_conf.tab.h: extensions/app_lte/app_lte_conf.tab.c
	@$(CMAKE_COMMAND) -E touch_nocreate extensions/app_lte/app_lte_conf.tab.h

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte.c.o: extensions/app_lte/CMakeFiles/app_lte.dir/flags.make
extensions/app_lte/CMakeFiles/app_lte.dir/app_lte.c.o: ../extensions/app_lte/app_lte.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object extensions/app_lte/CMakeFiles/app_lte.dir/app_lte.c.o"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/app_lte.dir/app_lte.c.o   -c /home/billing/freeDiameter/extensions/app_lte/app_lte.c

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app_lte.dir/app_lte.c.i"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/billing/freeDiameter/extensions/app_lte/app_lte.c > CMakeFiles/app_lte.dir/app_lte.c.i

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app_lte.dir/app_lte.c.s"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/billing/freeDiameter/extensions/app_lte/app_lte.c -o CMakeFiles/app_lte.dir/app_lte.c.s

extensions/app_lte/CMakeFiles/app_lte.dir/lex.app_lte_conf.c.o: extensions/app_lte/CMakeFiles/app_lte.dir/flags.make
extensions/app_lte/CMakeFiles/app_lte.dir/lex.app_lte_conf.c.o: extensions/app_lte/lex.app_lte_conf.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object extensions/app_lte/CMakeFiles/app_lte.dir/lex.app_lte_conf.c.o"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -I /home/billing/freeDiameter/extensions/app_lte -o CMakeFiles/app_lte.dir/lex.app_lte_conf.c.o   -c /home/billing/freeDiameter/build/extensions/app_lte/lex.app_lte_conf.c

extensions/app_lte/CMakeFiles/app_lte.dir/lex.app_lte_conf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app_lte.dir/lex.app_lte_conf.c.i"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -I /home/billing/freeDiameter/extensions/app_lte -E /home/billing/freeDiameter/build/extensions/app_lte/lex.app_lte_conf.c > CMakeFiles/app_lte.dir/lex.app_lte_conf.c.i

extensions/app_lte/CMakeFiles/app_lte.dir/lex.app_lte_conf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app_lte.dir/lex.app_lte_conf.c.s"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -I /home/billing/freeDiameter/extensions/app_lte -S /home/billing/freeDiameter/build/extensions/app_lte/lex.app_lte_conf.c -o CMakeFiles/app_lte.dir/lex.app_lte_conf.c.s

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_conf.tab.c.o: extensions/app_lte/CMakeFiles/app_lte.dir/flags.make
extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_conf.tab.c.o: extensions/app_lte/app_lte_conf.tab.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_conf.tab.c.o"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -I /home/billing/freeDiameter/extensions/app_lte -o CMakeFiles/app_lte.dir/app_lte_conf.tab.c.o   -c /home/billing/freeDiameter/build/extensions/app_lte/app_lte_conf.tab.c

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_conf.tab.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app_lte.dir/app_lte_conf.tab.c.i"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -I /home/billing/freeDiameter/extensions/app_lte -E /home/billing/freeDiameter/build/extensions/app_lte/app_lte_conf.tab.c > CMakeFiles/app_lte.dir/app_lte_conf.tab.c.i

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_conf.tab.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app_lte.dir/app_lte_conf.tab.c.s"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -I /home/billing/freeDiameter/extensions/app_lte -S /home/billing/freeDiameter/build/extensions/app_lte/app_lte_conf.tab.c -o CMakeFiles/app_lte.dir/app_lte_conf.tab.c.s

extensions/app_lte/CMakeFiles/app_lte.dir/ta_serv.c.o: extensions/app_lte/CMakeFiles/app_lte.dir/flags.make
extensions/app_lte/CMakeFiles/app_lte.dir/ta_serv.c.o: ../extensions/app_lte/ta_serv.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object extensions/app_lte/CMakeFiles/app_lte.dir/ta_serv.c.o"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/app_lte.dir/ta_serv.c.o   -c /home/billing/freeDiameter/extensions/app_lte/ta_serv.c

extensions/app_lte/CMakeFiles/app_lte.dir/ta_serv.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app_lte.dir/ta_serv.c.i"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/billing/freeDiameter/extensions/app_lte/ta_serv.c > CMakeFiles/app_lte.dir/ta_serv.c.i

extensions/app_lte/CMakeFiles/app_lte.dir/ta_serv.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app_lte.dir/ta_serv.c.s"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/billing/freeDiameter/extensions/app_lte/ta_serv.c -o CMakeFiles/app_lte.dir/ta_serv.c.s

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_mysql.c.o: extensions/app_lte/CMakeFiles/app_lte.dir/flags.make
extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_mysql.c.o: ../extensions/app_lte/app_lte_mysql.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_mysql.c.o"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/app_lte.dir/app_lte_mysql.c.o   -c /home/billing/freeDiameter/extensions/app_lte/app_lte_mysql.c

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_mysql.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app_lte.dir/app_lte_mysql.c.i"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/billing/freeDiameter/extensions/app_lte/app_lte_mysql.c > CMakeFiles/app_lte.dir/app_lte_mysql.c.i

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_mysql.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app_lte.dir/app_lte_mysql.c.s"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/billing/freeDiameter/extensions/app_lte/app_lte_mysql.c -o CMakeFiles/app_lte.dir/app_lte_mysql.c.s

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_server.c.o: extensions/app_lte/CMakeFiles/app_lte.dir/flags.make
extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_server.c.o: ../extensions/app_lte/app_lte_server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_server.c.o"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/app_lte.dir/app_lte_server.c.o   -c /home/billing/freeDiameter/extensions/app_lte/app_lte_server.c

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app_lte.dir/app_lte_server.c.i"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/billing/freeDiameter/extensions/app_lte/app_lte_server.c > CMakeFiles/app_lte.dir/app_lte_server.c.i

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app_lte.dir/app_lte_server.c.s"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/billing/freeDiameter/extensions/app_lte/app_lte_server.c -o CMakeFiles/app_lte.dir/app_lte_server.c.s

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_subscriber.c.o: extensions/app_lte/CMakeFiles/app_lte.dir/flags.make
extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_subscriber.c.o: ../extensions/app_lte/app_lte_subscriber.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_subscriber.c.o"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/app_lte.dir/app_lte_subscriber.c.o   -c /home/billing/freeDiameter/extensions/app_lte/app_lte_subscriber.c

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_subscriber.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app_lte.dir/app_lte_subscriber.c.i"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/billing/freeDiameter/extensions/app_lte/app_lte_subscriber.c > CMakeFiles/app_lte.dir/app_lte_subscriber.c.i

extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_subscriber.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app_lte.dir/app_lte_subscriber.c.s"
	cd /home/billing/freeDiameter/build/extensions/app_lte && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/billing/freeDiameter/extensions/app_lte/app_lte_subscriber.c -o CMakeFiles/app_lte.dir/app_lte_subscriber.c.s

# Object files for target app_lte
app_lte_OBJECTS = \
"CMakeFiles/app_lte.dir/app_lte.c.o" \
"CMakeFiles/app_lte.dir/lex.app_lte_conf.c.o" \
"CMakeFiles/app_lte.dir/app_lte_conf.tab.c.o" \
"CMakeFiles/app_lte.dir/ta_serv.c.o" \
"CMakeFiles/app_lte.dir/app_lte_mysql.c.o" \
"CMakeFiles/app_lte.dir/app_lte_server.c.o" \
"CMakeFiles/app_lte.dir/app_lte_subscriber.c.o"

# External object files for target app_lte
app_lte_EXTERNAL_OBJECTS =

extensions/app_lte.fdx: extensions/app_lte/CMakeFiles/app_lte.dir/app_lte.c.o
extensions/app_lte.fdx: extensions/app_lte/CMakeFiles/app_lte.dir/lex.app_lte_conf.c.o
extensions/app_lte.fdx: extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_conf.tab.c.o
extensions/app_lte.fdx: extensions/app_lte/CMakeFiles/app_lte.dir/ta_serv.c.o
extensions/app_lte.fdx: extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_mysql.c.o
extensions/app_lte.fdx: extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_server.c.o
extensions/app_lte.fdx: extensions/app_lte/CMakeFiles/app_lte.dir/app_lte_subscriber.c.o
extensions/app_lte.fdx: extensions/app_lte/CMakeFiles/app_lte.dir/build.make
extensions/app_lte.fdx: /usr/lib/x86_64-linux-gnu/libgcrypt.so
extensions/app_lte.fdx: /usr/lib/x86_64-linux-gnu/libgnutls.so
extensions/app_lte.fdx: /usr/lib/x86_64-linux-gnu/libmysqlclient.so
extensions/app_lte.fdx: extensions/app_lte/CMakeFiles/app_lte.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/billing/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C shared module ../app_lte.fdx"
	cd /home/billing/freeDiameter/build/extensions/app_lte && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app_lte.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extensions/app_lte/CMakeFiles/app_lte.dir/build: extensions/app_lte.fdx

.PHONY : extensions/app_lte/CMakeFiles/app_lte.dir/build

extensions/app_lte/CMakeFiles/app_lte.dir/clean:
	cd /home/billing/freeDiameter/build/extensions/app_lte && $(CMAKE_COMMAND) -P CMakeFiles/app_lte.dir/cmake_clean.cmake
.PHONY : extensions/app_lte/CMakeFiles/app_lte.dir/clean

extensions/app_lte/CMakeFiles/app_lte.dir/depend: extensions/app_lte/lex.app_lte_conf.c
extensions/app_lte/CMakeFiles/app_lte.dir/depend: extensions/app_lte/app_lte_conf.tab.c
extensions/app_lte/CMakeFiles/app_lte.dir/depend: extensions/app_lte/app_lte_conf.tab.h
	cd /home/billing/freeDiameter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/billing/freeDiameter /home/billing/freeDiameter/extensions/app_lte /home/billing/freeDiameter/build /home/billing/freeDiameter/build/extensions/app_lte /home/billing/freeDiameter/build/extensions/app_lte/CMakeFiles/app_lte.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extensions/app_lte/CMakeFiles/app_lte.dir/depend

