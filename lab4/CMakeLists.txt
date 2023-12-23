cmake_minimum_required(VERSION 3.19)
project(lab4)

set(CMAKE_CXX_STANDARD 14)
include_directories(C:/freeglut/include)

link_directories(C:/freeglut/lib/x64)
add_executable(lab4 main.cpp)

target_link_libraries(lab4 -lglu32 -lopengl32 -lfreeglut)
