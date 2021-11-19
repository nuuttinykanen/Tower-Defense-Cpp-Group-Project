cmake_minimum_required(VERSION 3.20)
project(tower-defense-12)
set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR c:/SFML-2.5.1/lib/cmake/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

set(SFML_STATIC_LIBRARIES TRUE)

add_executable(tower-defense-12 src/main.cpp src/Gui.cpp src/Gui.h src/game_states/window_state.cpp src/game_states/window_state.h src/game_states/menu_state.cpp src/game_states/menu_state.h src/game_states/game_state.cpp src/game_states/game_state.h src/game_states/level_select_state.cpp src/game_states/level_select_state.h src/game_states/level_editor_state.cpp src/game_states/level_editor_state.h)

# include_directories(headers /usr/include c:/SFML/include)


find_package(SFML COMPONENTS system window graphics network audio REQUIRED)


#include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(tower-defense-12 sfml-graphics sfml-audio)


#file(COPY libs DESTINATION ${CMAKE_BINARY_DIR})
