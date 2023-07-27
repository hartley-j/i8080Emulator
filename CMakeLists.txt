cmake_minimum_required(VERSION 3.25)
project(i8080Emulator)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})

add_subdirectory(src)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})