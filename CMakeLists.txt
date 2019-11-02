cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(events src/events.cpp)
target_link_libraries(events sfml-graphics sfml-window sfml-system)

add_executable(draw src/draw.cpp)
target_link_libraries(draw sfml-graphics sfml-window sfml-system)

add_executable(gameOfLife src/gameOfLife.cpp)
target_link_libraries(gameOfLife sfml-graphics sfml-window sfml-system)

add_executable(game src/game.cpp)
target_link_libraries(game sfml-graphics sfml-window sfml-system)
