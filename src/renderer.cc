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

namespace vkr {

Renderer::Renderer() = default;

Renderer::~Renderer() {}

void Renderer::run() {
  init();
  render();
  clean();
}

void Renderer::init() {}

void Renderer::render() {}

void Renderer::clean() {}

}  // namespace vkr
