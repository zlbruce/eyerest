find_package(PkgConfig REQUIRED)

pkg_check_modules(E REQUIRED enlightenment)

find_program(EDJECC NAMES edje_cc)
if (NOT EDJECC)
    message(SEND_ERROR "Could not find edje_cc")
endif(NOT EDJECC)

add_custom_command(OUTPUT eyerest.edj
    COMMAND ${EDJECC} -v -id ${CMAKE_CURRENT_SOURCE_DIR}/images
    ${CMAKE_CURRENT_SOURCE_DIR}/eyerest.edc
    ${CMAKE_CURRENT_BINARY_DIR}/eyerest.edj
    DEPENDS eyerest.edc images/gadcon_logo.png
    )
add_custom_command(OUTPUT e-module-eyerest.edj
    COMMAND ${EDJECC} -v -id ${CMAKE_CURRENT_SOURCE_DIR}/images
    ${CMAKE_CURRENT_SOURCE_DIR}/e-module-eyerest.edc
    ${CMAKE_CURRENT_BINARY_DIR}/e-module-eyerest.edj
    DEPENDS e-module-eyerest.edc images/module_icon.png
    )

add_custom_target(allbuild ALL
    DEPENDS eyerest.edj e-module-eyerest.edj)

_pkgconfig_invoke("enlightenment" E17 MODULES_DIR ""
--variable=modules)

set(INSTALL_DIR ${E17_MODULES_DIR}/eyerest/)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/eyerest.edj
    DESTINATION ${INSTALL_DIR})
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/e-module-eyerest.edj
    DESTINATION ${INSTALL_DIR})
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/module.desktop
    DESTINATION ${INSTALL_DIR})
