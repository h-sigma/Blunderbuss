cmake_minimum_required(VERSION 3.15)
project(Blunderbuss C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(Include)
include_directories(/usr/include/glm)
include_directories(3rdPartyLibs/DearImGui/)

#DearImGui Files
file(GLOB_RECURSE DearImGui_FILES
        ${CMAKE_SOURCE_DIR}/3rdPartyLibs/DearImGui/*.hpp
        ${CMAKE_SOURCE_DIR}/3rdPartyLibs/DearImGui/*.cpp)

#add_library(ImGui ${DearImGui_FILES})

#Blunderbuss Source Files
file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/Source/*.c
        ${CMAKE_SOURCE_DIR}/Source/*.cpp)

#Blunderbuss header files
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/Include/*.h
        ${CMAKE_SOURCE_DIR}/Include/*.hpp)

add_executable(Blunderbuss
        ${HEADER_FILES}
        ${SOURCE_FILES}
        ${DearImGui_FILES})
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

target_link_libraries(Blunderbuss OpenGL::GL sfml-graphics sfml-window sfml-system)
