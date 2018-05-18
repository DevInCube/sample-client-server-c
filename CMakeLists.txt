cmake_minimum_required(VERSION 2.8.7)

include_directories(app)
SET(CMAKE_C_FLAGS "-std=gnu99 -Werror -Wall -pedantic-errors -Wno-unused")

project(a.out)

file(GLOB SOURCES "app/*.c")

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} progbase jansson)

project(common)
file(GLOB COMMON_SOURCES "common/*.c")
add_library(${CMAKE_PROJECT_NAME} STATIC ${COMMON_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} progbase jansson)

project(client)
file(GLOB CLIENT_SOURCES "client/*.c")
add_executable(${CMAKE_PROJECT_NAME} ${CLIENT_SOURCES} ${COMMON_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} progbase jansson)

project(server)
file(GLOB SERVER_SOURCES "server/*.c")
add_executable(${CMAKE_PROJECT_NAME} ${SERVER_SOURCES} ${COMMON_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} progbase jansson)