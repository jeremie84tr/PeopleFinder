cmake_minimum_required(VERSION 3.29)
project(tp2)
include_directories("include")

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES
        "src/PeopleFinder/*.cpp"
)
add_executable(tp2 src/main.cpp ${SOURCES})
add_executable(tp2_test tests/main.cpp ${SOURCES})
