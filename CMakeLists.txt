cmake_minimum_required(VERSION 3.25)
project(i8080Emulator)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(SDL2_INCLUDE_DIR C:/libs/SDL/include)
    set(SDL2_LIB_DIR C:/libs/SDL/lib/x64)

    include_directories(${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_LIB_DIR})
endif(WIN32)

if(UNIX)
    find_package(SDL2 REQUIRED)
    include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})
endif(UNIX)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/40412d85124f7c6f3d88454583c4633e5e10fc8c.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(i8080Emulator src/main.cpp src/MMU.cpp src/MMU.h src/Display.cpp src/Display.h src/CPU.cpp src/CPU.h)

target_link_libraries(${PROJECT_NAME} gtest_main)
add_test(NAME DisplayTest COMMAND DisplayTest)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
endif(WIN32)

if(UNIX)
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif(UNIX)