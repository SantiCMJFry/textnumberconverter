cmake_minimum_required(VERSION 3.12)
project(textNumberConverter C CXX)

message("-----------------------------------------------------------")
message("Creating makefile of ${PROJECT_NAME} as ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

set(HEADERS
    include/textnumberconverter.hpp)

set(SOURCES
    src/textnumberconverter.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")


set(TEST_SOURCES
    src/main.cpp)

add_executable(${PROJECT_NAME}_test ${TEST_SOURCES})

target_link_libraries (${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})



