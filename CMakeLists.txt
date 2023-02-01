cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(RauchCasino VERSION 1.0)

link_directories(lib)
add_executable(RauchCasino main.cpp)

target_include_directories(RauchCasino PUBLIC include)
target_link_libraries(RauchCasino libsfml-window.a libsfml-system.a libsfml-graphics.a libsfml-audio.a -static-libgcc -static-libstdc++)