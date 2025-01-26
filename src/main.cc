/**
 * @file main.cc
 * @author MaoZ (mao.zhang233@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-06-06
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "renderer.h"

int main() {
  vkr::Renderer renderer{};

  try {
    renderer.render();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
