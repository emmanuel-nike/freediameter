# Install script for directory: /home/billing/freeDiameter/extensions

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/billing/freeDiameter/build/extensions/dict_nasreq/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/dict_eap/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/dict_dcca/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/dict_dcca_3gpp/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/dict_dcca_starent/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/dict_sip/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/app_lte/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/rt_busypeers/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/rt_default/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/rt_deny_by_size/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/rt_ignore_dh/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/rt_load_balance/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/rt_randomize/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/rt_redirect/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/rt_rewrite/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/acl_wl/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/dbg_dict_dump/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/dbg_loglevel/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/dbg_monitor/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/dbg_msg_timings/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/dbg_msg_dumps/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/dbg_rt/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/test_cc/cmake_install.cmake")
  include("/home/billing/freeDiameter/build/extensions/test_ccload/cmake_install.cmake")

endif()

