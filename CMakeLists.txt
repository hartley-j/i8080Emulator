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

add_executable(i8080Emulator main.cpp MMU.cpp MMU.h Display.cpp Display.h CPU.cpp CPU.h)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
endif(WIN32)

if(UNIX)
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif(UNIX)