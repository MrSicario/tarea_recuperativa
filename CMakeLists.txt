cmake_minimum_required(VERSION 3.29)
project(TareaRecuperativa_Log)
set(CMAKE_CXX_STANDARD 23)

add_compile_options(
        -O3
)

add_executable(main.cpp
        src/cpp/lib/perfect_hash/PerfectHash.hpp
        src/cpp/lib/perfect_hash/PerfectHash.hpp
        src/cpp/lib/perfect_hash/PrimeGen.hpp
        src/cpp/lib/perfect_hash/PrimeGen.hpp
        src/cpp/main.cpp
)
