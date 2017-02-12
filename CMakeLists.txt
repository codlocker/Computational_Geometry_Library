cmake_minimum_required(VERSION 3.5)
project(ComputGeoAlgos)

set(CMAKE_CXX_STANDARD 11)
find_package(CGAL REQUIRED)
include(${CGAL_USE_FILE})

set(SOURCE_FILES main.cpp )
add_executable(ComputGeoAlgos ${SOURCE_FILES})
target_link_libraries(ComputGeoAlgos ${CGAL_LIBS})