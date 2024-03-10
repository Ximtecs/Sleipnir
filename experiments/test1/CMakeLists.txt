## This assumes test1.cpp is meant to be an executable that links against main_program_lib and task_lib
#add_executable(test1 test1.cpp)
#
## Specify where CMake can find the libraries
## Since we're not installing the libraries, we need to tell CMake where to find them during the build
#target_link_libraries(test1 PRIVATE main_program_lib task_lib)
#
## This is to ensure the test1 executable knows where to find its header files from main and tasks
#target_include_directories(test1 PRIVATE ${PROJECT_SOURCE_DIR}/src/main)
#target_include_directories(test1 PRIVATE ${PROJECT_SOURCE_DIR}/src/tasks)
#
#set_target_properties(test1 PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#)


add_executable(test1 test1.cpp)

# Link with the main_program_lib and task_lib libraries
target_link_libraries(test1 PRIVATE main_program_lib task_lib)

# Assuming test1 might need OpenMP as well
if(OpenMP_CXX_FOUND)
    target_link_libraries(test1 PRIVATE OpenMP::OpenMP_CXX)
endif()

set_target_properties(test1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
