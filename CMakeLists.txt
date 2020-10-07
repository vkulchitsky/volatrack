cmake_minimum_required(VERSION 3.5)

project(Volatrack LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET_NAME volatrack)

file(GLOB_RECURSE SOURCES_D "physics/data/*.cpp")
file(GLOB_RECURSE SOURCES_E "physics/engine/*.cpp")
file(GLOB_RECURSE SOURCES_IO "io/*.cpp")
file(GLOB SOURCES "*.cpp")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${TARGET_NAME} ${SOURCES_D} ${SOURCES} ${SOURCES_E}
    ${SOURCES_IO})

target_link_libraries(${TARGET_NAME} Qt5::Widgets)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(tests)
