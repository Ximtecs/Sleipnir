set(DATA_ARRAYS_SOURCES
    StaticArrayBase.hpp
    StaticArrayCPU.hpp
    StaticArrayCPU.cpp
    StaticArrayGPU.hpp
    StaticArrayGPU.cpp
)

add_library(data_arrays ${DATA_ARRAYS_SOURCES})

target_include_directories(data_arrays PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# If you're using OpenMP
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(data_arrays PUBLIC OpenMP::OpenMP_CXX)
endif()