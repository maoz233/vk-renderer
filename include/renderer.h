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
#include <vulkan/vulkan.h>

#include <array>
#include <glm/glm.hpp>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "gui.h"
#include "window.h"

namespace vkr {

struct Vertex {
  glm::vec3 pos;
  glm::vec3 color;
  glm::vec2 texCoord;

  static VkVertexInputBindingDescription getBindingDescription();
  static std::array<VkVertexInputAttributeDescription, 3>
  getAttributeDescriptions();

  bool operator==(const Vertex& other) const;
};

struct UniformBufferObject {
  alignas(16) glm::mat4 model;
  alignas(16) glm::mat4 view;
  alignas(16) glm::mat4 proj;
};

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete();
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

class Renderer {
 public:
  Renderer();
  ~Renderer();

  void setFramebufferResized(bool resized);

  void run();

 private:
  std::unique_ptr<Window> window_;
  VkInstance instance_;
  VkDebugUtilsMessengerEXT debugMessenger_;
  VkSurfaceKHR surface_;
  VkPhysicalDevice physicalDevice_ = VK_NULL_HANDLE;
  VkSampleCountFlagBits msaaSamples_ = VK_SAMPLE_COUNT_1_BIT;
  VkDevice device_;
  VkQueue graphicsQueue_;
  VkQueue presentQueue_;
  VkSwapchainKHR swapChain_;
  std::vector<VkImage> swapChainImages_;
  VkFormat swapChainImageFormat_;
  VkExtent2D swapChainExtent_;
  std::vector<VkImageView> swapChainImageViews_;
  VkRenderPass renderPass_;
  VkDescriptorSetLayout descriptorSetLayout_;
  VkPipelineLayout pipelineLayout_;
  VkPipeline graphicsPipeline_;
  std::vector<VkFramebuffer> swapChainFrameBuffers_;
  VkCommandPool commandPool_;
  std::vector<Vertex> vertices_;
  std::vector<uint32_t> indices_;
  VkBuffer vertexBuffer_;
  VkDeviceMemory vertexBufferMemory_;
  VkBuffer indexBuffer_;
  VkDeviceMemory indexBufferMemory_;
  std::vector<VkBuffer> uniformBuffers_;
  std::vector<VkDeviceMemory> uniformBuffersMemory_;
  std::vector<void*> uniformBuffersMapped_;
  VkImage colorImage_;
  VkDeviceMemory colorImageMemory_;
  VkImageView colorImageView_;
  VkImage depthImage_;
  VkDeviceMemory depthImageMemory_;
  VkImageView depthImageView_;
  uint32_t mipLevels_;
  VkImage textureImage_;
  VkDeviceMemory textureImageMemory_;
  VkImageView textureImageView_;
  VkSampler textureSampler_;
  VkDescriptorPool descriptorPool_;
  std::vector<VkDescriptorSet> descriptorSets_;
  std::vector<VkCommandBuffer> commandBuffers_;
  std::vector<VkSemaphore> imageAvailableSemaphores_;
  std::vector<VkSemaphore> renderFinishiedSemephores_;
  std::vector<VkFence> inFlightFences_;
  uint32_t currentFrame_ = 0;
  bool framebufferResized_ = false;
  std::unique_ptr<GUI> gui_;

  void initVulkan();
  void drawFrame();

  void createInstance();
  void setupDebugMessenger();
  void createSurface();
  void pickPhysicalDevice();
  void createLogicalDevice();
  void createSwapChain();
  void createImageViews();
  void createRenderPass();
  void createDescriptorSetLayout();
  void createGraphicsPipeline();
  void createCommandPool();
  void createColorResources();
  void createDepthResources();
  void createFramebuffers();
  void loadModel();
  void createVertexBuffer();
  void createIndexBufffer();
  void createUniformBuffers();
  void createTextureImage();
  void createTextureImageView();
  void createTextureSampler();
  void createDescriptorPool();
  void createDescriptorSets();
  void createCommandBuffers();
  void createSyncObjects();
  void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
  void recreateSwapchain();
  void updateUniformBuffer(uint32_t currentFrame);

  std::vector<const char*> getRequiredExtensions();
  bool checkValidationLayerSupport();
  void populateDebugMessengerCreateInfo(
      VkDebugUtilsMessengerCreateInfoEXT& createInfo);
  bool isDeviceSuitable(VkPhysicalDevice device);
  int rateDeviceSuitability(VkPhysicalDevice device);
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(
      const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(
      const std::vector<VkPresentModeKHR>& availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
  VkShaderModule createShaderModule(const std::vector<char>& code);
  void cleanupSwapChain();
  void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                    VkMemoryPropertyFlags properties, VkBuffer& buffer,
                    VkDeviceMemory& bufferMemory);
  void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
  void createImage(uint32_t width, uint32_t height, uint32_t mipLevels,
                   VkSampleCountFlagBits numSamples, VkFormat format,
                   VkImageTiling tiling, VkImageUsageFlags usage,
                   VkMemoryPropertyFlags properties, VkImage& image,
                   VkDeviceMemory& imageMemory);
  void transitionImageLayout(VkImage image, VkFormat format,
                             VkImageLayout oldLayout, VkImageLayout newLayout,
                             uint32_t mipLevels);
  void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width,
                         uint32_t height);
  void generateMipMaps(VkImage image, VkFormat imageFormat, int32_t texWidth,
                       int32_t texHeight, uint32_t mipLevels);
  VkImageView createImageView(VkImage image, VkFormat format,
                              VkImageAspectFlags aspectFlags,
                              uint32_t mipLevels);
  VkFormat findDepthFormat();
  bool hasStencilComponent(VkFormat format);
  VkSampleCountFlagBits getMaxUsableSampleCount();

  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
  bool checkDeviceExtensionSupport(VkPhysicalDevice device);
  SwapChainSupportDetails querySwapChainSupprt(VkPhysicalDevice device);
  uint32_t findMemoryType(uint32_t typeFilter,
                          VkMemoryPropertyFlags properties);
  VkCommandBuffer beginSingleTimeCommands();
  void endSingleTimeCommands(VkCommandBuffer commandBuffer);
  VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates,
                               VkImageTiling tiling,
                               VkFormatFeatureFlags features);

  static VkResult CreateDebugUtilsMessengerEXT(
      VkInstance instance,
      const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
      const VkAllocationCallbacks* pAllocator,
      VkDebugUtilsMessengerEXT* pDebugMessenger);
  static void DestroyDebugUtilsMessengerEXT(
      VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
      const VkAllocationCallbacks* pAllocator);
  static VKAPI_ATTR VkBool32 VKAPI_CALL
  debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageServity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData);
  static std::vector<char> readFile(const std::string& filename);
  static void checkVKResult(VkResult result);
};

}  // namespace vkr

#endif  // VK_RENDERER_RENDERER_H_
