# This CMakeLists.txt project is for Ubuntu only
project(redgpu_memory_allocator)
cmake_minimum_required(VERSION 2.8.12)
link_libraries(
  /opt/RedGpuSDK/libredgpu.so
)
add_library(redgpu_memory_allocator SHARED
  redgpu_memory_allocator.cpp
)
