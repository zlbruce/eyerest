# Find the required Libaries
find_package(KDE4 REQUIRED)
include(KDE4Defaults)
 
add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
   )
 
# We add our source code here
set(eyerest_SRCS plasma-eyerest.cpp)
qt4_add_dbus_interface(eyerest_SRCS ${PROJECT_SOURCE_DIR}/eyerest-dbus.xml eyerest_dbus)
 
# Now make sure all files get to the right place
kde4_add_plugin(plasma_applet_eyerest ${eyerest_SRCS})
target_link_libraries(plasma_applet_eyerest
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS})
 
install(TARGETS plasma_applet_eyerest
        DESTINATION ${PLUGIN_INSTALL_DIR})
 
install(FILES plasma-applet-eyerest.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})
