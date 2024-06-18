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

file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/shaders/*.spv)
foreach(SHADER ${SHADERS})
  get_filename_component(SHADER_NAME ${SHADER} NAME)
  add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/shaders/${SHADER_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SHADER} ${CMAKE_BINARY_DIR}/shaders/${SHADER_NAME}
    DEPENDS ${SHADER}
  )
  list(APPEND SHADER_TARGETS ${CMAKE_BINARY_DIR}/shaders/${SHADER_NAME})
endforeach()
set(COPY_SHADERS copy-shaders)
add_custom_target(${COPY_SHADERS} ALL DEPENDS ${SHADER_TARGETS})

file(GLOB TEXTURES ${CMAKE_SOURCE_DIR}/textures/*)
foreach(TEXTURE ${TEXTURES})
  get_filename_component(TEXTURE_NAME ${TEXTURE} NAME)
  add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/textures/${TEXTURE_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TEXTURE} ${CMAKE_BINARY_DIR}/textures/${TEXTURE_NAME}
    DEPENDS ${TEXTURE}
  )
  list(APPEND TEXTURE_TARGETS ${CMAKE_BINARY_DIR}/textures/${TEXTURE_NAME})
endforeach()
set(COPY_TEXTURE copy-textures)
add_custom_target(${COPY_TEXTURE} ALL DEPENDS ${TEXTURE_TARGETS})

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cc)

if(WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/)
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})
add_dependencies(${PROJECT_NAME} ${COPY_SHADERS} ${COPY_TEXTURE})

include_directories(${PROJECT_NAME} PRIVATE 
  ${PROJECT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/lib/glm-1.0.1
  ${CMAKE_SOURCE_DIR}/lib/imgui-1.90.8
  ${CMAKE_SOURCE_DIR}/lib/imgui-1.90.8/backends
  ${CMAKE_SOURCE_DIR}/lib/stb
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
  Vulkan::Vulkan 
  glfw
)
