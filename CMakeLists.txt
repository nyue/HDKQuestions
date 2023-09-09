cmake_minimum_required(VERSION 3.12)

project(HDKQuestions)

#find_package(HDK REQUIRED)
#include_directories(${HDK_INCLUDE_DIR})

find_package(Houdini REQUIRED)

add_subdirectory(PRM)
#add_subdirectory(VEX)
#add_subdirectory(CVEX)
