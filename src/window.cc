/**
 * @file window.cc
 * @author MaoZ (mao.zhang233@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-01-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "window.h"

#include <iostream>
#include <stdexcept>

namespace vkr {

Window::Window(const WindowConfig& config) {
  if (!glfwInit()) {
    throw std::runtime_error("Failed to init GLFW!");
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  this->window_ = glfwCreateWindow(config.width, config.height, config.title,
                                   nullptr, nullptr);
  if (!this->window_) {
    throw std::runtime_error("Failed to create GLFW window!");
  }

  glfwSetWindowUserPointer(this->window_, config.user);
  glfwSetFramebufferSizeCallback(this->window_, config.fbcb);
}

Window::~Window() {
  glfwDestroyWindow(this->window_);
  glfwTerminate();
}

GLFWwindow* Window::getInstance() const { return this->window_; }

bool Window::shouldClose() const {
  return glfwWindowShouldClose(this->window_);
}

void Window::getFramebufferSize(int* width, int* height) const {
  glfwGetFramebufferSize(this->window_, width, height);
}

}  // namespace vkr
