cmake_minimum_required(VERSION 3.12)
project(textNumberConverter C CXX)

message("-----------------------------------------------------------")
message("Creating makefile of ${PROJECT_NAME} as ${CMAKE_BUILD_TYPE}")

if(UNIX)
    set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
    if(DEFINED COVERAGE)
        LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")
        include(CodeCoverage)
        APPEND_COVERAGE_COMPILER_FLAGS() 
        setup_target_for_coverage_lcov(NAME ${PROJECT_NAME}_coverage  EXECUTABLE ${PROJECT_NAME}_test)
    endif()
endif()

set(HEADERS
    include/textnumberconverter.hpp)

set(SOURCES
    src/textnumberconverter.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")

set(TEST_SOURCES
    src/test.cpp)

add_executable(${PROJECT_NAME}_test ${TEST_SOURCES})


set(MAIN_SOURCES
    src/main.cpp)

add_executable(${PROJECT_NAME}_main ${MAIN_SOURCES})

target_link_libraries (${PROJECT_NAME}_main PRIVATE ${PROJECT_NAME})

if(CMAKE_COMPILER_IS_GNUCXX)
   target_link_libraries (${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})
endif()




