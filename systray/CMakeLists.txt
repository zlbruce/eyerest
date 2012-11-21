set(SRC_LIST
    tray.c
    eyerest-dbus.c
    )
find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0 gio-2.0)
pkg_check_modules(GIOUNIX gio-unix-2.0)
pkg_check_modules(GTK3 gtk+-3.0)
pkg_check_modules(GTK2 gtk+-2.0)
set(SRC_LIBS ${GLIB_LIBRARIES})

if(GIOUNIX_FOUND)
    include_directories(${GIOUNIX_INCLUDE_DIRS})
    link_directories(${GIOUNIX_LIBRARY_DIRS})
endif(GIOUNIX_FOUND)

if(GTK3_FOUND)
    include_directories(${GTK3_INCLUDE_DIRS})
    link_directories(${GTK3_LIBRARY_DIRS})
    set(SRC_LIBS ${SRC_LIBS} ${GTK3_LIBRARIES})
elseif(GTK2_FOUND)
    include_directories(${GTK2_INCLUDE_DIRS})
    link_directories(${GTK2_LIBRARY_DIRS})
    set(SRC_LIBS ${SRC_LIBS} ${GTK2_LIBRARIES})
else(GTK3_FOUND)
    message(SEND_ERROR "Could not find gtk devel")
endif(GTK3_FOUND)

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

add_executable(eyerest-tray ${SRC_LIST})
TARGET_LINK_LIBRARIES(eyerest-tray ${SRC_LIBS})
INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/eyerest-tray DESTINATION bin)
