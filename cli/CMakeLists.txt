set(SRC_LIST
    eyerest-cli.c
    eyerest-dbus.c
    )
find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0 gio-2.0)
pkg_check_modules(GIOUNIX gio-unix-2.0)

if(GIOUNIX_FOUND)
    include_directories(${GIOUNIX_INCLUDE_DIRS})
    link_directories(${GIOUNIX_LIBRARY_DIRS})
endif(GIOUNIX_FOUND)

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

find_program(GDBUSCODEGEN NAMES gdbus-codegen)
if (NOT GDBUSCODEGEN)
    message(SEND_ERROR "Could not find gdbus-codegen")
endif(NOT GDBUSCODEGEN)

add_custom_command(OUTPUT eyerest-dbus.c
    COMMAND ${GDBUSCODEGEN} --generate-c-code=eyerest-dbus ${PROJECT_SOURCE_DIR}/eyerest-dbus.xml
    DEPENDS ${PROJECT_SOURCE_DIR}/eyerest-dbus.xml
    )
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(eyerest-cli ${SRC_LIST})
TARGET_LINK_LIBRARIES(eyerest-cli ${GLIB_LIBRARIES})
INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/eyerest-cli DESTINATION bin)
