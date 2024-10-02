cmake_minimum_required(VERSION 3.18)

set(PROJECT_NAME "main_benchmark")
project(${PROJECT_NAME} CXX)

message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
if (CMAKE_BUILD_TYPE MATCHES Debug)
message(STATUS "Building in debug mode")
	add_definitions(-g -O0)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
endif()

set(CMAKE_CXX_STANDARD 20)

find_package(benchmark REQUIRED)

set(SOURCES main_benchmark.cpp)

function(add_test_executable test_name)
	add_executable(
		${test_name}
		${SOURCES}
		${HEADERS})

	target_link_libraries(${PROJECT_NAME} benchmark::benchmark)
	target_include_directories(
		${test_name}
		PRIVATE
		${CMAKE_SOURCE_DIR})
endfunction()

add_test_executable(${PROJECT_NAME})
