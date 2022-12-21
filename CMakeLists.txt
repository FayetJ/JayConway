cmake_minimum_required(VERSION 3.5)

project(conway LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_NAME "conway")
set(sources Game.hpp Game.cpp states/Life.hpp states/Life.cpp InputManager.hpp InputManager.cpp states/GameState.hpp
    states/monobold.ttf states/GameState.cpp states/LifeMenu.hpp states/LifeMenu.cpp)
add_executable(conway main.cpp ${sources})

install(TARGETS conway
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ../ ./ states)
target_link_libraries(${EXECUTABLE_NAME} SDL2_ttf ${SDL2_LIBRARIES} )
