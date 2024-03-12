set(TIMING_SOURCES
    timing.cpp
    timing.hpp
)

add_library(timing_lib ${TIMING_SOURCES})


target_include_directories(timing_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link with OpenMP
if(OpenMP_CXX_FOUND)
    target_link_libraries(timing_lib PUBLIC OpenMP::OpenMP_CXX)
endif()
