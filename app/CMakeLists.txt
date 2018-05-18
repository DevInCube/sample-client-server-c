cmake_minimum_required(VERSION 2.8.7)

include_directories(.)
SET(CMAKE_C_FLAGS "-std=gnu99 -Werror -Wall -pedantic-errors -Wno-unused")

project(a.out)

file(GLOB SOURCES "*.c")

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} progbase jansson)
