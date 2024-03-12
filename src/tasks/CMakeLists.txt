set(TASK_SOURCES
    patch.cpp
    patch.hpp
    task.cpp
    task.hpp
)

add_library(task_lib ${TASK_SOURCES})


target_include_directories(task_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(task_lib PUBLIC data_arrays_lib)


# Link with OpenMP
if(OpenMP_CXX_FOUND)
    target_link_libraries(task_lib PUBLIC OpenMP::OpenMP_CXX)
endif()
