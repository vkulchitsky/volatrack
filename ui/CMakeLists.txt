file(GLOB_RECURSE SOURCES_UI "*.cpp")
file(GLOB_RECURSE FORMS "*.ui")
file(GLOB_RECURSE SOURCES_RE "rendering/*.cpp")

add_executable(${TARGET_NAME_G}
    ${SOURCES_IO} ${SOURCES_UI} ${SOURCES_RE} ${SOURCES_DA}
    ${FORMS}
  )

target_link_libraries(volagraph PRIVATE Qt5::Widgets)
