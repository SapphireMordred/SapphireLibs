cmake_minimum_required(VERSION 3.1)
project(Sapphire)

include_directories("../../external/")

if(UNIX)
  include_directories(${MYSQLCLIENT_INCLUDE_DIRS})
  
else()
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../external/MySQL/")
endif()

message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

file(GLOB UTILS_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB UTILS_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(mysqlConnector ${UTILS_PUBLIC_INCLUDE_FILES} ${UTILS_SOURCE_FILES})

include_directories(${Boost_INCLUDE_DIRS})
