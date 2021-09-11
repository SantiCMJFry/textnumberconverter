cmake_minimum_required(VERSION 3.12)
project(textNumberConverter C CXX)

message("-----------------------------------------------------------")
message("Creating makefile of ${PROJECT_NAME} as ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

set(HEADERS
    include/textnumberconverter.hpp)

set(SOURCES
    src/main.cpp
    src/textnumberconverter.cpp)

#add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           INTERFACE $<INSTALL_INTERFACE:include>)

##set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${EXPORTABLE_HEADERS}")
#
#install(TARGETS ${PROJECT_NAME} EXPORT ${PRODUCT_TARGET}
#                ARCHIVE DESTINATION lib
#                LIBRARY DESTINATION lib
#                RUNTIME DESTINATION bin
#                PUBLIC_HEADER DESTINATION include/${PROJECT_NAME})

#target_link_libraries (${PROJECT_NAME} PRIVATE tools
#                                               iodevices)

