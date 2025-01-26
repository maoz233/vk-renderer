cmake_minimum_required(VERSION 3.29)

project(vk-renderer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuration
configure_file(
  ${PROJECT_SOURCE_DIR}/config.h.in
  ${PROJECT_BINARY_DIR}/config.h
)

# Vulkan
find_package(Vulkan REQUIRED)
# GLFW
add_subdirectory(third-party/glfw)
# Dear ImGui
set(IMGUI_SOURCES
    third-party/imgui/imgui.cpp
    third-party/imgui/imgui_demo.cpp
    third-party/imgui/imgui_draw.cpp
    third-party/imgui/imgui_tables.cpp
    third-party/imgui/imgui_widgets.cpp
    third-party/imgui/backends/imgui_impl_glfw.cpp
    third-party/imgui/backends/imgui_impl_vulkan.cpp
)

# Assets
file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)

# Shaders
file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/shaders/*.spv)
foreach(SHADER ${SHADERS})
  file(COPY ${SHADER} DESTINATION ${CMAKE_BINARY_DIR}/shaders)
endforeach()

# Source files
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cc)

# Output directory on Windows
if(WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/)
endif()

# Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})

# Include directories
include_directories(${PROJECT_NAME} PRIVATE 
  ${PROJECT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/third-party/glm
  ${CMAKE_SOURCE_DIR}/third-party/imgui
  ${CMAKE_SOURCE_DIR}/third-party/imgui/backends
  ${CMAKE_SOURCE_DIR}/third-party/stb
  ${CMAKE_SOURCE_DIR}/third-party/tinyobjloader
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
  Vulkan::Vulkan 
  glfw
)
