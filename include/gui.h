/**
 * @file gui.h
 * @author MaoZ (mao.zhang233@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-01-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef VK_RENDERER_GUI_H_
#define VK_RENDERER_GUI_H_

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

namespace vkr {

struct GUIConfig {
  GLFWwindow* window;
  VkInstance instance;
  VkPhysicalDevice physicalDevice;
  VkDevice device;
  uint32_t queueFamily;
  VkQueue queue;
  VkDescriptorPool descriptorPool;
  VkRenderPass renderPass;
  uint32_t minImageCount;
  uint32_t imageCount;
  VkSampleCountFlagBits msaaSamples;
  VkPipelineCache pipelineCache;
  uint32_t subpass;
  uint32_t descriptorPoolSize;
  bool useDynamicRendering;
#ifdef IMGUI_IMPL_VULKAN_HAS_DYNAMIC_RENDERING
  VkPipelineRenderingCreateInfoKHR pipelineRenderingCreateInfo;
#endif
  const VkAllocationCallbacks* allocator;
  void (*checkVkResultFn)(VkResult err);
  VkDeviceSize minAllocationSize;
};

class GUI {
 public:
  GUI() = delete;
  GUI(const GUIConfig& config);
  ~GUI();

  void draw(VkCommandBuffer commandBuffer);
};

}  // namespace vkr

#endif  // VK_RENDERER_GUI_H_
