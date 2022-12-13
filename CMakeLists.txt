cmake_minimum_required(VERSION 3.5)

project(conway LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_NAME "conway")
set(sources Game.hpp Game.cpp Life.hpp Life.cpp InputManager.hpp InputManager.cpp)
add_executable(conway main.cpp ${sources})

install(TARGETS conway
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${EXECUTABLE_NAME} ${SDL2_LIBRARIES})
