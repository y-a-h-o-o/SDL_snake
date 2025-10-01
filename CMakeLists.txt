# Minimum Required Version
cmake_minimum_required(VERSION 3.15...4.0)

# Useless stuff honestly... I have no idea what I am doing lol 
# First time using cmake
project(
	SDL_snake
	VERSION 1.0 
	LANGUAGES CXX
)

# sets output for build objects. 
# DLL will go in Build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")

# Add SDL 
add_subdirectory(extern/SDL EXCLUDE_FROM_ALL) 

# Add src subdirectory 
add_subdirectory(src) 
