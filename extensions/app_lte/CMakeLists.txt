# The app_lte extension
PROJECT("WG LTE Diameter Application" C)

# Parser files
BISON_FILE(ta_conf.y)
FLEX_FILE(ta_conf.l)
SET_SOURCE_FILES_PROPERTIES(lex.ta_conf.c ta_conf.tab.c PROPERTIES COMPILE_FLAGS "-I ${CMAKE_CURRENT_SOURCE_DIR}")

# List of source files
SET( APP_LTE_SRC
	app_lte.h
	lte_common.h
	app_lte.c
	lex.ta_conf.c
	ta_conf.tab.c
	ta_conf.tab.h
	ta_dict.c
	ta_serv.c
	app_lte_mysql.h
	app_lte_mysql.c
)

# Compile as a module
FD_ADD_EXTENSION(app_lte ${APP_LTE_SRC})


####
## INSTALL section ##

INSTALL(TARGETS app_lte
	LIBRARY DESTINATION ${INSTALL_EXTENSIONS_SUFFIX}
	COMPONENT freeDiameter-lte-server)
