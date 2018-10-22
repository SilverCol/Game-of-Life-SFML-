cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)

add_executable(run src/main.cpp)
target_link_libraries(run sfml-graphics sfml-window sfml-system)
