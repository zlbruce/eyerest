set(SRC_LIST
    config.c
    dbus.c
    main.c
    state.c
    timer.c
    xevent.c
    xlock.c
    eyerest-dbus.c
    )
find_package(PkgConfig REQUIRED)

pkg_check_modules(X11 REQUIRED x11 xtst xft)
pkg_check_modules(GLIB REQUIRED glib-2.0 gio-2.0)
pkg_check_modules(GIOUNIX gio-unix-2.0)
if(GIOUNIX_FOUND)
    include_directories(${GIOUNIX_INCLUDE_DIRS})
    link_directories(${GIOUNIX_LIBRARY_DIRS})
endif(GIOUNIX_FOUND)

include_directories(${X11_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS})
link_directories(${X11_LIBRARY_DIRS} ${GLIB_LIBRARY_DIRS})

find_program(GDBUSCODEGEN NAMES gdbus-codegen)
if (NOT GDBUSCODEGEN)
    message(SEND_ERROR "Could not find gdbus-codegen")
endif(NOT GDBUSCODEGEN)

add_custom_command(OUTPUT eyerest-dbus.c
    COMMAND ${GDBUSCODEGEN} --generate-c-code=eyerest-dbus ${PROJECT_SOURCE_DIR}/eyerest-dbus.xml
    DEPENDS ${PROJECT_SOURCE_DIR}/eyerest-dbus.xml
    )
include_directories(${CMAKE_CURRENT_BINARY_DIR})

macro(dbus_add_activation_service _sources)
    foreach (_i ${_sources})
        get_filename_component(_service_file ${_i} ABSOLUTE)
        string(REGEX REPLACE "\\.service.*$" ".service" _output_file ${_i})
        set(_target ${CMAKE_CURRENT_BINARY_DIR}/${_output_file})
        configure_file(${_service_file} ${_target})
        install(FILES ${_target} DESTINATION ${DBUS_SERVICES_INSTALL_DIR} )
    endforeach (_i ${ARGN})
endmacro(dbus_add_activation_service _sources)

_pkgconfig_invoke("dbus-1" DBUS SERVICES_INSTALL_DIR ""
--variable=session_bus_services_dir)

if (DBUS_SERVICES_INSTALL_DIR)
    dbus_add_activation_service(org.zlbruce.eyerest.service.in)
endif(DBUS_SERVICES_INSTALL_DIR)

add_executable(eyerest-daemon ${SRC_LIST})
TARGET_LINK_LIBRARIES(eyerest-daemon ${X11_LIBRARIES} ${GLIB_LIBRARIES})
INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/eyerest-daemon DESTINATION bin)
