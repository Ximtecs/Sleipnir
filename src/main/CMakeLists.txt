add_library(main_program_lib main.cpp main.hpp)

target_include_directories(main_program_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link with task_lib to resolve dependencies
target_link_libraries(main_program_lib PUBLIC task_lib timing_lib)

# Additionally, link with OpenMP if it's being used within main_program_lib
if(OpenMP_CXX_FOUND)
    target_link_libraries(main_program_lib PUBLIC OpenMP::OpenMP_CXX)
endif()
