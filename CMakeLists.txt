cmake_minimum_required(VERSION 3.15)
project(Blunderbuss C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(Include)
include_directories(/usr/include/glm)

file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/Source/*.c
        ${CMAKE_SOURCE_DIR}/Source/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/Include/*.h
        ${CMAKE_SOURCE_DIR}/Include/*.hpp)

add_executable(Blunderbuss
        ${HEADER_FILES}
        ${SOURCE_FILES})

target_link_libraries(Blunderbuss sfml-graphics sfml-window sfml-system)