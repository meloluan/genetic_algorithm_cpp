# genetic_algorithm_cpp
# Solutions to CEC2017 Constrained Optimization Issues C01-C05
# Copyright 2023, Luan
cmake_minimum_required(VERSION 3.1)
project(genetic_algorithm_cpp C CXX)
set(PROJECT_DESCRIPTION   "Solutions to CEC2017 Constrained Optimization Issues C01-C05")
set(PROJECT_AUTHOR        "Luan Melo")
set(PROJECT_URL           "https://github.com/meloluan/genetic_algorithm_cpp")
set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "1")

# Build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")


# ---------------------------------------------------------
# Features
# ---------------------------------------------------------
# add_subdirectory(external)
# enable_testing()
# add_subdirectory(test)
# add_subdirectory(doc)

file(GLOB SOURCE src/*.cpp)
add_library(genetic_algorithm_cpp_lib SHARED ${SOURCE})
set_target_properties(genetic_algorithm_cpp_lib PROPERTIES
    "OUTPUT_NAME" "genetic_algorithm_cpp"
    "INCLUDE_DIRECTORIES" "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
install(TARGETS genetic_algorithm_cpp_lib EXPORT genetic_algorithm_cpp DESTINATION ${CMAKE_SOURCE_DIR}/lib)
export(TARGETS genetic_algorithm_cpp_lib FILE ${CMAKE_BINARY_DIR}/genetic_algorithm_cpp-config.cmake)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC src/)     
target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/libgenetic_algorithm_cpp.so)
