cmake_minimum_required(VERSION 3.1)

project(coobaker)

set(CMAKE_CXX_STANDARD 11)

include_directories("include")

set(sources "include/maptypes.h"
            "source/maptypes.cpp"
            "include/radiance.h"
            "source/radiance.cpp"
            "include/ddscm.h"
            "source/ddscm.cpp"
            "source/main.cpp")

add_executable(${PROJECT_NAME} ${sources})
