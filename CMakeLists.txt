cmake_minimum_required(VERSION 3.15)
project(CPP_OGL_TEMPL VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    src/main.cpp

    src/renderer/Texture.cpp
    src/renderer/Buffer.cpp
    src/renderer/Shader.cpp

    src/input/Input.cpp

    external/glad/src/glad.c

    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
    external/imgui/imgui_demo.cpp # can be commented out
)

include_directories(include)
include_directories(external/glad/include)
include_directories(external/glfw/include)
include_directories(external/imgui)
include_directories(external/imgui/backends)

# add GLFW as a submodule
add_subdirectory(external/glfw)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE BUILD_DEBUG=1) # 0=RELEASE, 1=DEBUG
endif()
