cmake_minimum_required(VERSION 3.29)
project(Tarea_Recuperativa_Log)
set(CMAKE_CXX_STANDARD 23)

add_compile_options(
        -O3
)

add_executable(main.o
        src/cpp/lib/PerfectHash.hpp
        src/cpp/lib/PerfectHash.cpp
        src/cpp/main.cpp
)
