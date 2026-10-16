
cmake_minimum_required(VERSION 3.20)

project(LearnOpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(LearnOpenGL
        src/main.cpp
        src/glad.c
        ../include/glad/glad.h
        ../include/glad/glad.h
)

target_include_directories(LearnOpenGL PRIVATE
        ../include
)

target_link_libraries(LearnOpenGL PRIVATE
        glfw
        OpenGL::GL
)
