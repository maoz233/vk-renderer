cmake_minimum_required(VERSION 3.29)

project(vk-renderer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vulkan
find_package(Vulkan REQUIRED)
# GLFW
add_subdirectory(lib/glfw-3.4)
# Dear ImGui
set(IMGUI_SOURCES
    lib/imgui-1.90.8/imgui.cpp
    lib/imgui-1.90.8/imgui_demo.cpp
    lib/imgui-1.90.8/imgui_draw.cpp
    lib/imgui-1.90.8/imgui_tables.cpp
    lib/imgui-1.90.8/imgui_widgets.cpp
    lib/imgui-1.90.8/backends/imgui_impl_glfw.cpp
    lib/imgui-1.90.8/backends/imgui_impl_vulkan.cpp
)

file(GLOB SOURCES "src/*.cc")

add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})

include_directories(${PROJECT_NAME} PRIVATE 
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/lib/glm-1.0.1
  ${CMAKE_SOURCE_DIR}/lib/imgui-1.90.8
  ${CMAKE_SOURCE_DIR}/lib/imgui-1.90.8/backends
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
  Vulkan::Vulkan 
  glfw
)
