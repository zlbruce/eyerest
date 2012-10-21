AUX_SOURCE_DIRECTORY(. SRC_LIST)
add_executable(eyerest-daemon ${SRC_LIST})
TARGET_LINK_LIBRARIES(eyerest-daemon event X11 Xtst)
