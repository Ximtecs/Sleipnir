cmake_minimum_required(VERSION 3.10)
project(Sleipnir VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Since the executable will depend on these, they need to be included before the experiments
add_subdirectory(src)
add_subdirectory(experiments)
