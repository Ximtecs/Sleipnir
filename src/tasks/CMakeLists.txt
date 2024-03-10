add_library(task_lib task.cpp task.hpp)

target_include_directories(task_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link with OpenMP
if(OpenMP_CXX_FOUND)
    target_link_libraries(task_lib PUBLIC OpenMP::OpenMP_CXX)
endif()
