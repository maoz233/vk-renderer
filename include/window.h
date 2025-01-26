/**
 * @file window.h
 * @author MaoZ (mao.zhang233@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-01-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef VK_RENDERER_WINDOW_H_
#define VK_RENDERER_WINDOW_H_

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vkr {

struct WindowConfig {
  int width;
  int height;
  const char* title;
  void* user;                   // window user pointer
  GLFWframebuffersizefun fbcb;  // framebuffer size callback
};

class Window {
 public:
  Window() = delete;
  Window(const WindowConfig& config);
  ~Window();

  GLFWwindow* getInstance() const;

  bool shouldClose() const;
  void getFramebufferSize(int* width, int* height) const;

 private:
  GLFWwindow* window_;
};

}  // namespace vkr

#endif  // VK_RENDERER_WINDOW_H_
