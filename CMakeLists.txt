cmake_minimum_required(VERSION 3.25)
project(i8080Emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/buildtools/sdl2)
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} src/main.cpp)