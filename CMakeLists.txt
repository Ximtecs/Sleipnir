cmake_minimum_required(VERSION 3.10)
project(Sleipnir VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# Find OpenMP
find_package(OpenMP REQUIRED)

# Add the compiler flags for offloading
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -foffload=-lm")

# Add the compiler flags for offloading
add_definitions(-DUSE_GPU)

# Since the executable will depend on these, they need to be included before the experiments
add_subdirectory(src)
add_subdirectory(experiments)
