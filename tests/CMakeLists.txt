include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(DisplayTest
        DisplayTest.cpp)
add_executable(CPUTest
        CPUTest.cpp)

target_link_libraries(DisplayTest
PRIVATE
        GTest::GTest
        SDL2::SDL2main
        SDL2::SDL2-static
        Display
)

target_link_libraries(CPUTest
PRIVATE
        GTest::GTest
        CPU
)

add_test(CPUTest CPUTest)
add_test(DisplayTest DisplayTest)