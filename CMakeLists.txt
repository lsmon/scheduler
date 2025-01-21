cmake_minimum_required(VERSION 3.5.0)
project(scheduler LANGUAGES C CXX)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(INC include/Task.hpp
        include/Scheduler.hpp)
set(SRC sources/Scheduler.cpp)

set(LIB_NAME _${PROJECT_NAME}-${PROJECT_VERSION})

add_library(${LIB_NAME} STATIC ${INC} ${SRC})

include(cpack/cpack.cmake)
include(tests/tests.cmake)
