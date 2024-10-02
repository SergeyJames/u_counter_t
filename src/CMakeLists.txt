cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

set(PROJECT_NAME "u_counter_t")

message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
if (CMAKE_BUILD_TYPE MATCHES Debug)
message(STATUS "Building in debug mode")
	add_definitions(-g -O0)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
endif()

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})


if(WITH_TEST)
	add_subdirectory(Test)
endif()

if(WITH_BENCHMARK)
	add_subdirectory(Benchmark)
endif()