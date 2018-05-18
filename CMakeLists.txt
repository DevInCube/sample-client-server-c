cmake_minimum_required(VERSION 2.8.7)

project(a.out)

include_directories(app)
file(GLOB SOURCES "app/*.c")

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} progbase jansson)