cmake_minimum_required(VERSION 3.14)
project(opentonano)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/CPM.cmake)

# find_package(OpenVDB REQUIRED)

cpmaddpackage(
  "https://github.com/AcademySoftwareFoundation/openvdb.git#v10.0.0")
# if(openvdb_ADDED) target_include_directories( openvdb INTERFACE
# "$<BUILD_INTERFACE:${Imath_SOURCE_DIR}/src/*.h>") endif()

add_executable(opentonano src/main.cpp)

target_link_libraries(opentonano openvdb)
