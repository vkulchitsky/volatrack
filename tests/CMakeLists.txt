file(GLOB_RECURSE SOURCES_T "*.cpp")

add_executable(tests ${SOURCES_T} ${SOURCES_DA} ${SOURCES_A} ${SOURCES_E}
    ${SOURCES_IO})
target_link_libraries(tests Qt5::Widgets)
