set(DATA_ARRAYS_SOURCES
    ArrayCPU.cpp
    ArrayCPU.hpp
    ArrayGPU.cpp
    ArrayGPU.hpp
    ArrayBase.hpp
)

add_library(data_arrays_lib ${DATA_ARRAYS_SOURCES})

target_include_directories(data_arrays_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


if(OpenMP_CXX_FOUND)
    target_link_libraries(data_arrays_lib PUBLIC OpenMP::OpenMP_CXX)
endif()