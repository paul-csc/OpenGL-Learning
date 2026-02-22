set(SOURCES
    src/main.cpp
    src/renderer.cpp
    src/shader.cpp
    src/index_buffer.cpp
    src/vertex_array.cpp
    src/vertex_buffer.cpp
)

add_executable(Core ${SOURCES})

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
    GLFW_INCLUDE_NONE
)

target_link_libraries(Core PRIVATE
    glfw
    glad
    glm
)

target_include_directories(Core PRIVATE src)

# Set working directory for VS debugger
set_target_properties(Core PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Core"
)