AUX_SOURCE_DIRECTORY(. SRC_LIST)
add_executable(eye_rest ${SRC_LIST})
TARGET_LINK_LIBRARIES(eye_rest event X11 Xtst)
