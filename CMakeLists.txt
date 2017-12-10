cmake_minimum_required(VERSION 3.1)
project(Sapphire)

include(cmake/compiler.cmake)
include(cmake/FindBoost.cmake)

if(UNIX)
  find_package(PkgConfig REQUIRED)

  pkg_search_module(MYSQLCLIENT REQUIRED mysqlclient)
endif()

find_package(Boost 1.63.0)
if(NOT Boost_FOUND)
  message(FATAL_ERROR "Boost not found")
endif()

add_subdirectory(sapphire)
