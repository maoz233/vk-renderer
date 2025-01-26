/**
 * @file gui.cc
 * @author MaoZ (mao.zhang233@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-01-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "gui.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>

namespace vkr {

GUI::GUI(const GUIConfig& config) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForVulkan(config.window, true);

  ImGui_ImplVulkan_InitInfo info{};
  info.Instance = config.instance;
  info.PhysicalDevice = config.physicalDevice;
  info.Device = config.device;
  info.QueueFamily = config.queueFamily;
  info.Queue = config.queue;
  info.PipelineCache = config.pipelineCache;
  info.DescriptorPool = config.descriptorPool;
  info.RenderPass = config.renderPass;
  info.Subpass = config.subpass;
  info.MinImageCount = config.minImageCount;
  info.ImageCount = config.imageCount;
  info.MSAASamples = config.msaaSamples;
  info.Allocator = config.allocator;
  info.CheckVkResultFn = config.checkVkResultFn;
  ImGui_ImplVulkan_Init(&info);
}

GUI::~GUI() {
  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void GUI::draw(VkCommandBuffer commandBuffer) {
  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // ImGui::ShowDemoWindow();

  ImGui::Begin("Profiler");

  ImGuiIO& io = ImGui::GetIO();
  ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate,
              io.Framerate);

  ImGui::End();

  ImGui::Render();
  ImDrawData* drawData = ImGui::GetDrawData();
  ImGui_ImplVulkan_RenderDrawData(drawData, commandBuffer);
}

}  // namespace vkr