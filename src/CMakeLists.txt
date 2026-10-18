
cmake_minimum_required(VERSION 3.20)

project(LearnOpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(LearnOpenGL
        main.cpp
        glad.c
        ../include/stb_image.h
        stb_image.cpp
)

target_include_directories(LearnOpenGL PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(LearnOpenGL PRIVATE
        glfw
        OpenGL::GL
        ${CMAKE_DL_LIBS}
)

# Copy shaders next to the executable on every build
add_custom_target(copy_shaders ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/Triangle.vert
        ${CMAKE_CURRENT_SOURCE_DIR}/Triangle.frag
        $<TARGET_FILE_DIR:LearnOpenGL>
)
add_dependencies(LearnOpenGL copy_shaders)