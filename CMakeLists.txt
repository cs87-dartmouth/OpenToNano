cmake_minimum_required(VERSION 3.14)
project(opentonano)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenVDB REQUIRED)

file(GLOB OPENTONANO_SOURCE src/*.cpp)

add_executable(
  opentonano
  # source files
  ${OPENTONANO_SOURCE})

target_link_libraries(opentonano OpenVDB::openvdb)
