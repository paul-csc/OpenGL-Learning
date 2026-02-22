cmake_minimum_required(VERSION 3.21)
project(Core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages installed via vcpkg
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# stb is header-only
find_path(STB_INCLUDE_DIRS "stb_image.h")

# Source files
set(SOURCES
    src/main.cpp
    src/renderer.cpp
    src/shader.cpp
    src/index_buffer.cpp
    src/vertex_array.cpp
    src/vertex_buffer.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${STB_INCLUDE_DIRS}
    src
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw
    glad::glad
    glm::glm
)
