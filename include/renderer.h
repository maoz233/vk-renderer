/**
 * @file renderer.h
 * @author MaoZ (mao.zhang233@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-06-06
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef VK_RENDERER_RENDERER_H_
#define VK_RENDERER_RENDERER_H_

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

namespace vkr {

class Renderer {
 public:
  Renderer();
  ~Renderer();

  void run();

 private:
  GLFWwindow* window_;
  VkInstance instance_;

  void init();
  void render();
  void clean();

  void initWindow();
  void initVulkan();

  void createInstance();
};

}  // namespace vkr

#endif  // VK_RENDERER_RENDERER_H_
