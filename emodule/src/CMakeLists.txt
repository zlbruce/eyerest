set(SRC_LIST
    e_mod_main.c
    dbus_eyerest.c
    )
cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig REQUIRED)

pkg_check_modules(E REQUIRED enlightenment)

include_directories(${E_INCLUDE_DIRS})
link_directories(${E_LIBRARY_DIRS})

#find_program(EDJECC NAMES edje_cc)
#if (NOT EDJECC)
#    message(SEND_ERROR "Could not find edje_cc")
#endif(NOT EDJECC)

_pkgconfig_invoke("enlightenment" E17 MODULES_DIR ""
--variable=modules)
_pkgconfig_invoke("enlightenment" E17 RELEASE_DIR ""
--variable=release)

set(hostos "${CMAKE_SYSTEM_NAME}")
if ("${hostos}" STREQUAL "Linux")
    set(hostos "linux-gnu")
endif()

set(INSTALL_DIR
    ${E17_MODULES_DIR}/eyerest/${hostos}-${CMAKE_SYSTEM_PROCESSOR}-${E17_RELEASE_DIR})

add_library(eyerest SHARED ${SRC_LIST})
TARGET_LINK_LIBRARIES(eyerest ${E_LIBRARIES})
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/libeyerest.so
    DESTINATION ${INSTALL_DIR}
    RENAME module.so)
