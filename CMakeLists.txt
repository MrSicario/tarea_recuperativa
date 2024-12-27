cmake_minimum_required(VERSION 3.30.5)
project(Tarea_Recuperativa_Log)
set(CMAKE_CXX_STANDARD 23)

add_executable(tarea
        main.cpp
)

add_subdirectory(lib)

target_link_libraries(tarea PUBLIC PerfectHash)

target_include_directories(tarea PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/lib")