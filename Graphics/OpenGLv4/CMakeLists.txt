cmake_minimum_required(VERSION 3.16)

project(CamaraOpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(
    camara

    src/main.cpp
    src/Application.cpp
    src/Camera.cpp
    src/Mesh.cpp
    src/PrimitiveFactory.cpp
    src/Scene.cpp
    src/Shader.cpp
    src/Transform.cpp

    external/glad/src/gl.c
)

target_compile_definitions(camara PRIVATE GLFW_INCLUDE_NONE)

target_include_directories(
    camara
    PRIVATE
    include
    external/glad/include
)

target_link_libraries(
    camara
    PRIVATE
    glfw
    OpenGL::GL
    glm::glm
)