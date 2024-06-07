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

namespace vkr {

class Renderer {
 public:
  Renderer();
  ~Renderer();

  void run();

 private:
  void init();
  void render();
  void clean();
};

}  // namespace vkr
