cmake_minimum_required(VERSION 3.16)
project(MY1STGAME LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(game src/main.cpp src/game.cpp)
target_link_libraries(game PRIVATE sfml-graphics sfml-system sfml-window)
target_compile_features(game PRIVATE cxx_std_17)
target_include_directories(game PRIVATE SYSTEM ${PROJECT_SOURCE_DIR}/include)

