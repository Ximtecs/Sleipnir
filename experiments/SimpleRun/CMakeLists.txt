add_executable(simpleRun.x simpleRun.cpp)

# Link with the main_program_lib and task_lib libraries
target_link_libraries(simpleRun.x PRIVATE main_program_lib task_lib)

# Assuming test1 might need OpenMP as well
if(OpenMP_CXX_FOUND)
    target_link_libraries(simpleRun.x PRIVATE OpenMP::OpenMP_CXX)
endif()

set_target_properties(simpleRun.x PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
