cmake_minimum_required(VERSION 3.19)
project(lab1)

set(CMAKE_CXX_STANDARD 14)
include_directories(C:/freeglut/include)

link_directories(C:/freeglut/lib/x64)
add_executable(lab1 main.cpp)

target_link_libraries(lab1 -lglu32 -lopengl32 -lfreeglut)