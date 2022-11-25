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

cpmaddpackage(
  NAME
  openvdb
  URL
  https://github.com/AcademySoftwareFoundation/openvdb/archive/refs/tags/v9.1.0.zip
  OPTIONS
  "OPENVDB_BUILD_CORE ON"
  "OPENVDB_BUILD_BINARIES OFF"
  "USE_NANOVDB ON"
  "NANOVDB_ALLOW_FETCHCONTENT ON"
  "NANOVDB_USE_ZLIB ON"
  "NANOVDB_BUILD_TOOLS OFF"
  "NANOVDB_USE_TBB OFF"
  "NANOVDB_USE_OPENVDB OFF"
  "NANOVDB_USE_BLOSC OFF"
  "NANOVDB_USE_CUDA OFF"
  "NANOVDB_USE_OPTIX OFF"
  "NANOVDB_USE_OPENCL OFF")
if(openvdb_ADDED)
  get_target_property(type nanovdb TYPE)
  message(STATUS "NanoVDB library type: ${type}")
  # if(zlibstatic_ADDED) message(STATUS "Adding zlib dependency to nanovdb")
  add_dependencies(nanovdb zlibstatic)
  target_include_directories(nanovdb INTERFACE ${ZLIB_INCLUDE_DIR})
  # list(APPEND DARTS_DEPEND nanovdb)
endif()
# list(APPEND DARTS_PRIVATE_LIBS nanovdb) endif()

add_executable(opentonano src/main.cpp)

target_link_libraries(opentonano openvdb)
