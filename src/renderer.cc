/**
 * @file renderer.cc
 * @author MaoZ (mao.zhang233@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-06-06
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "renderer.h"

#include <stdexcept>
#include <vector>

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "config.h"

namespace vkr {

Renderer::Renderer() = default;

Renderer::~Renderer() {}

void Renderer::run() {
  init();
  render();
  clean();
}

void Renderer::init() {
  initWindow();
  initVulkan();
}

void Renderer::render() {
  while (!glfwWindowShouldClose(window_)) {
    glfwPollEvents();
  }
}

void Renderer::clean() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

void Renderer::initWindow() {
  if (!glfwInit()) {
    throw std::runtime_error("Failed to init GLFW!");
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window_ =
      glfwCreateWindow(VK_RENDERER_WINDOW_WIDTH, VK_RENDERER_WINDOW_HEIGHT,
                       VK_RENDERER_WINDOW_TITLE, nullptr, nullptr);
  if (!window_) {
    throw std::runtime_error("Failed to create GLFW window!");
  }
}

void Renderer::initVulkan() { createInstance(); }

void Renderer::createInstance() {
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = VK_RENDERRER_NAME;
  appInfo.applicationVersion =
      VK_MAKE_VERSION(VK_RENDERER_VERSION_MAJOR, VK_RENDERER_VERSION_MINOR,
                      VK_RENDERER_VERSION_PATCH);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion =
      VK_MAKE_VERSION(VK_RENDERER_VERSION_MAJOR, VK_RENDERER_VERSION_MINOR,
                      VK_RENDERER_VERSION_PATCH);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  std::vector<const char*> requiredExtensions{};
  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
  for (uint32_t i = 0; i < glfwExtensionCount; i++) {
    requiredExtensions.push_back(glfwExtensions[i]);
  }
#ifdef __APPLE__
  requiredExtensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
#ifdef __APPLE__
  createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif
  createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
  createInfo.ppEnabledExtensionNames = requiredExtensions.data();
  createInfo.enabledLayerCount = 0;

  VkResult result = vkCreateInstance(&createInfo, nullptr, &instance_);
  if (VK_SUCCESS != result) {
    throw std::runtime_error("Failed to create Vulkan instance!");
  }
}

}  // namespace vkr
