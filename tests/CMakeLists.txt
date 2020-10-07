file(GLOB_RECURSE SOURCES_T "*.cpp")

add_executable(tests ${SOURCES_T} ${SOURCES_D})
target_link_libraries(tests Qt5::Widgets)
