add_library(task_lib task.cpp task.hpp)
target_include_directories(task_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
