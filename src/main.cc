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
#include <iostream>

#include "renderer.h"

int main() {
  std::clog << "Starting..." << std::endl;

  Renderer* renderer = new Renderer();
  renderer->run();

  std::cout << "Terminating..." << std::endl;

  return 0;
}
