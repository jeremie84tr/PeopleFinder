cmake_minimum_required(VERSION 3.29)
project(tp2)
include_directories("include")

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES
        "src/main.cpp"
        "src/PeopleFinder/*.cpp"
        # Add other directories as needed
)
add_executable(tp2 ${SOURCES})
