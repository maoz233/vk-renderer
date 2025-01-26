/**
 * @file camera.h
 * @author MaoZ (mao.zhang233@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-01-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef VK_RENDERER_CAMERA_H_
#define VK_RENDERER_CAMERA_H_

#include <glm/glm.hpp>

namespace vkr {

enum Mode {
  None,
  Tumble,
  Track,
  Dolly,
};

class Camera {
 public:
  Camera();

  glm::mat4 getViewMatrix();

 private:
  Mode mode_;
  glm::vec3 up_;
  glm::vec3 right_;
  glm::vec3 forward_;
  glm::vec3 eye_;
  glm::vec3 center_;
  float pitch_;
  float yaw_;
};

}  // namespace vkr

#endif  // VK_RENDERER_CAMERA_H_
