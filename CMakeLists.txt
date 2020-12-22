
cmake_minimum_required(VERSION 2.8)
 
project(DVFcomparison)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
 
add_executable(DVFcomparison MACOSX_BUNDLE DVFcomparison.cxx)
target_link_libraries(DVFcomparison ${ITK_LIBRARIES})
