add_library(main_program_lib main.cpp main.hpp)

# Link with task_lib to resolve the dependency on Task
target_link_libraries(main_program_lib PRIVATE task_lib)

# Ensure main_program_lib exposes its header files, and also inherits task_lib's headers
target_include_directories(main_program_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
