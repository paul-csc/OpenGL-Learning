include(FetchContent)

# GLFW
find_package(glfw3 3.4 QUIET)

if (NOT glfw3_FOUND)
    FetchContent_Declare(
        glfw3
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
    )

    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(glfw3)
endif()

# OpenGL
find_package(OpenGL REQUIRED)

# GLAD
FetchContent_Declare(
    glad
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/Dav1dde/glad/archive/refs/tags/v2.0.8.zip
)

set(FETCHCONTENT_QUIET NO)
FetchContent_MakeAvailable(glad)

add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=4.6)
set_target_properties(glad PROPERTIES FOLDER "Dependencies")

# GLM
find_package(glm 1.0.1 QUIET)

if (NOT glm_FOUND)
    FetchContent_Declare(
        glm
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.zip
    )

    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(glm)
endif()
set_target_properties(glm PROPERTIES FOLDER "Dependencies")
