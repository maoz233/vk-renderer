/**
 * @file camera.cc
 * @author MaoZ (mao.zhang233@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-01-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "camera.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace vkr {

Camera::Camera() {
  this->mode_ = Mode::None;
  this->up_ = glm::vec3(0.f, 1.f, 0.f);
  this->right_ = glm::vec3(1.f, 0.f, 0.f);
  this->forward_ = glm::vec3(0.f, 0.f, -1.f);
  this->eye_ = glm::vec3(0.f, 0.f, 0.f);
  this->center_ = glm::vec3(0.f, 0.f, -1.f);
  this->pitch_ = 0.f;
  this->yaw_ = 0.f;
}

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(this->eye_, this->center_, this->up_);
}

}  // namespace vkr