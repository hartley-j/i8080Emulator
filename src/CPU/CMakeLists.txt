add_library(CPU CPU.cpp)

target_include_directories(CPU PUBLIC include)
target_link_libraries(CPU MMU)