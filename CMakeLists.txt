cmake_minimum_required(VERSION 3.0)

project(TP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

include (CTest)

add_executable(comunidad comunidad_main.cpp Comunidad.cpp)
add_executable(comunidad_tests comunidad_tests.cpp Comunidad.cpp)

target_link_libraries(
  comunidad_tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(comunidad_tests)
