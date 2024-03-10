add_executable(ArrayTests.x StaticGPUtest.cpp)


target_link_libraries(ArrayTests.x PRIVATE data_arrays_lib)


set_target_properties(ArrayTests.x PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
