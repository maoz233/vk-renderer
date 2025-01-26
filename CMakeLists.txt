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

file(GLOB MODELS ${CMAKE_SOURCE_DIR}/models/*)
foreach(MODEL ${MODELS})
  get_filename_component(MODEL_NAME ${MODEL} NAME)
  add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/models/${MODEL_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MODEL} ${CMAKE_BINARY_DIR}/models/${MODEL_NAME}
    DEPENDS ${MODEL}
  )
  list(APPEND MODEL_TARGETS ${CMAKE_BINARY_DIR}/models/${MODEL_NAME})
endforeach()
set(COPY_MODELS copy-models)
add_custom_target(${COPY_MODELS} ALL DEPENDS ${MODEL_TARGETS})

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cc)

if(WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/)
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})
add_dependencies(${PROJECT_NAME} ${COPY_SHADERS} ${COPY_TEXTURES} ${COPY_MODELS})

include_directories(${PROJECT_NAME} PRIVATE 
  ${PROJECT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/third-party/glm
  ${CMAKE_SOURCE_DIR}/third-party/imgui
  ${CMAKE_SOURCE_DIR}/third-party/imgui/backends
  ${CMAKE_SOURCE_DIR}/third-party/stb
  ${CMAKE_SOURCE_DIR}/third-party/tinyobjloader
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
  Vulkan::Vulkan 
  glfw
)