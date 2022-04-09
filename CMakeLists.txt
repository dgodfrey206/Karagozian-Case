cmake_minimum_required(VERSION 3.10)

# set the project name
project(wordsearch)

# set another project
project(nearest)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# change the working directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# add the executable
add_executable(wordsearch superwordsearch.cpp)

# add the executable
add_executable(nearest nearest_neighbor.cpp)

