# CMakeList.txt : CMake project for T-G, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("T-G")

add_subdirectory ("3rdparty")

# Add source to this project's executable.
add_executable (T-G "Main.cpp")

target_link_libraries (T-G sfml-audio sfml-graphics sfml-window sfml-system sfml-main)

# TODO: Add tests and install targets if needed.
