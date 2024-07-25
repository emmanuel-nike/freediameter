# The app_lte extension
PROJECT("WG LTE Diameter Application" C)

INCLUDE (CheckCSourceCompiles)

# Find MySQL 
FIND_PACKAGE(MySQL REQUIRED)
FIND_PACKAGE(Gcrypt REQUIRED)
INCLUDE_DIRECTORIES(${MySQL_INCLUDE_DIR})

# Check for my_bool, deprecated in MySQL 8.0
SET(CHECK_MYSQL_MY_BOOL "
#include <mysql.h>
int main() {
my_bool f;
}")
SET(CMAKE_REQUIRED_INCLUDES ${MySQL_INCLUDE_DIR})
SET(CMAKE_REQUIRED_LIBRARIES ${MySQL_LIBRARY})
CHECK_C_SOURCE_COMPILES("${CHECK_MYSQL_MY_BOOL}" HAVE_MYSQL_MY_BOOL)
IF (HAVE_MYSQL_MY_BOOL)
  ADD_DEFINITIONS(-DHAVE_MYSQL_MY_BOOL)
ENDIF()

# Parser files
BISON_FILE(app_lte_conf.y)
FLEX_FILE(app_lte_conf.l)
SET_SOURCE_FILES_PROPERTIES(lex.app_lte_conf.c app_lte_conf.tab.c PROPERTIES COMPILE_FLAGS "-I ${CMAKE_CURRENT_SOURCE_DIR}")

# List of source files
SET( APP_LTE_SRC
	app_lte.h
	app_lte_defs.h
	app_lte_subscriber.h
	app_lte_common.h
	app_lte.c
	lib_app_lte.h
	lex.app_lte_conf.c 
	app_lte_conf.tab.c
	app_lte_conf.tab.h
	ta_serv.c
	app_lte_mysql.h
	app_lte_mysql.c
	app_lte_server.h
	app_lte_server.c
	app_lte_subscriber.c
)

# Compile as a module
FD_ADD_EXTENSION(app_lte ${APP_LTE_SRC})

TARGET_LINK_LIBRARIES(app_lte ${GCRYPT_LIBRARY} ${GNUTLS_LIBRARIES} ${MySQL_LIBRARY} )


####
## INSTALL section ##

INSTALL(TARGETS app_lte
	LIBRARY DESTINATION ${INSTALL_EXTENSIONS_SUFFIX}
	COMPONENT freeDiameter-lte-server)
