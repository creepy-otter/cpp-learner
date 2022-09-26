cmake_minimum_required(VERSION 3.20.0)

# CPP 17 forces RVO even for -O0.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")

project(my_project_name VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory(./src bin)