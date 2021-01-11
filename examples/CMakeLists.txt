file(GLOB_RECURSE SOURCES_T "*.cpp")

add_executable(examples ${SOURCES_T} ${SOURCES_DA} ${SOURCES_A} ${SOURCES_E}
    ${SOURCES_IO})
target_link_libraries(examples Qt5::Widgets)

