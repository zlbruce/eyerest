# Find the required Libaries
find_package(KDE4 REQUIRED)
include(KDE4Defaults)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${KDE4_INCLUDES}
    )

FIND_PROGRAM(GETTEXT_MSGFMT_EXECUTABLE msgfmt)

IF(NOT GETTEXT_MSGFMT_EXECUTABLE)
    MESSAGE(
        "------
        NOTE: msgfmt not found. Translations will *not*
        be installed
        ------")
ELSE(NOT GETTEXT_MSGFMT_EXECUTABLE)
    SET(catalogname plasma_applet_eyerest)
    ADD_CUSTOM_TARGET(translations ALL)

    FILE(GLOB PO_FILES *.po)
    FOREACH(_poFile ${PO_FILES})
        GET_FILENAME_COMPONENT(_poFileName ${_poFile} NAME)
        STRING(REGEX REPLACE "^${catalogname}_?" "" _langCode ${_poFileName} )
        STRING(REGEX REPLACE "\\.po$" "" _langCode ${_langCode} )

        IF( _langCode )
            GET_FILENAME_COMPONENT(_lang ${_poFile} NAME_WE)
            SET(_gmoFile ${CMAKE_CURRENT_BINARY_DIR}/${_lang}.gmo)
            ADD_CUSTOM_COMMAND(TARGET translations
                COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} --check -o ${_gmoFile} ${_poFile}
                DEPENDS ${_poFile})
            INSTALL(FILES ${_gmoFile} 
                DESTINATION ${LOCALE_INSTALL_DIR}/${_langCode}/LC_MESSAGES/ 
                RENAME ${catalogname}.mo)
        ENDIF( _langCode )
    ENDFOREACH(_poFile ${PO_FILES})
ENDIF(NOT GETTEXT_MSGFMT_EXECUTABLE)


# We add our source code here
set(eyerest_SRCS plasma-eyerest.cpp)
qt4_add_dbus_interface(eyerest_SRCS ${PROJECT_SOURCE_DIR}/eyerest-dbus.xml eyerest_dbus)

kde4_add_ui_files(eyerest_SRCS eyerest-config.ui)

# Now make sure all files get to the right place
kde4_add_plugin(plasma_applet_eyerest ${eyerest_SRCS})
target_link_libraries(plasma_applet_eyerest
    ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS})

install(TARGETS plasma_applet_eyerest
    DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES plasma-applet-eyerest.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})
