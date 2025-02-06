cmake_minimum_required(VERSION 3.11)
include(FetchContent)

project(OpenGLProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

# SDL3
set(SDL_STATIC ON)
set(SDL_SHARED OFF)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.2
)

# glm
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)

FetchContent_MakeAvailable(SDL3 glm)

# ImGui
add_subdirectory(third_party/imgui)

# Add the executable
add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL SDL3::SDL3-static glm::glm imgui)
target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_STATIC)
