AUX_SOURCE_DIRECTORY(. SRC_LIST)
add_executable(eyerest-daemon ${SRC_LIST})
find_package(PkgConfig REQUIRED)

pkg_check_modules(EVENT REQUIRED libevent)
pkg_check_modules(X11 REQUIRED x11)
pkg_check_modules(XTST REQUIRED xtst)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories(${EVENT_INCLUDE_DIRS} ${X11_INCLUDE_DIRS} ${XTST_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS})
link_directories(${EVENT_LIBRARY_DIRS} ${X11_LIBRARY_DIRS} ${XTST_LIBRARY_DIRS} ${GLIB_INCLUDE_DIRS})


TARGET_LINK_LIBRARIES(eyerest-daemon ${EVENT_LIBRARIES} ${X11_LIBRARIES} ${XTST_LIBRARIES} ${GLIB_LIBRARIES})
