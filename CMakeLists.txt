cmake_minimum_required(VERSION 3.16)
project(cubf LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CUDA_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(CMAKE_CXX_FLAGS "-g -Wall")
  set(CMAKE_CUDA_FLAGS "-arch=sm_75 -g")
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
  set(CMAKE_CXX_FLAGS "-O3")
  set(CMAKE_CUDA_FLAGS "-arch=sm_75 -O3")
else()
  message(STATUS "Warning: invalid CMAKE_BUILD_TYPE provided: ${CMAKE_BUILD_TYPE}")
endif()

set(SOURCES ${SOURCES}
  bloom_filter.cpp
  cu_bloom_filter.cu
  data_generator.cpp
  kernels.cu
)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
