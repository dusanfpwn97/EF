#include "first_app.h"

#include <stdexcept>
#include <array>
#include <iostream>
#include <cassert>

namespace ef
{

FirstApp::FirstApp() {
    loadModels();
    createPipelineLayout();
    recreateSwapchain();
    createCommandBuffers();
}

FirstApp::~FirstApp() {
    vkDestroyPipelineLayout(efDevice.device(), pipelineLayout, nullptr);
}

void FirstApp::run() {
    while (!efWindow.shouldClose()) {
        glfwPollEvents();
        drawFrame();
    }

    vkDeviceWaitIdle(efDevice.device());
}

void FirstApp::createPipelineLayout() {
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;
    if (vkCreatePipelineLayout(efDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
        VK_SUCCESS) {
        throw std::runtime_error("failed to create pipeline layout!");
    }
}

void FirstApp::createPipeline() {

    assert(efSwapChain != nullptr && "Cannot create pipeline before swap chain");
    assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

    PipelineConfigInfo pipelineConfig{};
    EfPipeline::defaultPipelineConfigInfo(pipelineConfig);

    pipelineConfig.renderPass = efSwapChain->getRenderPass();
    pipelineConfig.pipelineLayout = pipelineLayout;
    efPipeline = std::make_unique<EfPipeline>(
        efDevice,
        "shaders/simple_shader.vert.spv",
        "shaders/simple_shader.frag.spv",
        pipelineConfig);
}

void FirstApp::createCommandBuffers() {
    commandBuffers.resize(efSwapChain->imageCount());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = efDevice.getCommandPool();
    allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

    if (vkAllocateCommandBuffers(efDevice.device(), &allocInfo, commandBuffers.data()) !=
        VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }

    
}

void FirstApp::freeCommandBuffers()
{
    vkFreeCommandBuffers(efDevice.device(), efDevice.getCommandPool(), static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
    commandBuffers.clear();
}


void FirstApp::recordCommandBuffer(int imageIndex) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = efSwapChain->getRenderPass();
    renderPassInfo.framebuffer = efSwapChain->getFrameBuffer(imageIndex);

    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = efSwapChain->getSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
    clearValues[1].depthStencil = { 1.0f, 0 };
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);


    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(efSwapChain->getSwapChainExtent().width);
    viewport.height = static_cast<float>(efSwapChain->getSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{ {0, 0}, efSwapChain->getSwapChainExtent() };
    vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
    vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);

    efPipeline->bind(commandBuffers[imageIndex]);
    efModel->bind(commandBuffers[imageIndex]);
    efModel->draw(commandBuffers[imageIndex]);

    vkCmdEndRenderPass(commandBuffers[imageIndex]);
    if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}


void FirstApp::drawFrame() {
    uint32_t imageIndex;
    auto result = efSwapChain->acquireNextImage(&imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        recreateSwapchain();
        return;
    }
    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    recordCommandBuffer(imageIndex);
    result = efSwapChain->submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || efWindow.wasWindowsResized())
    {
        efWindow.resetWindowResizedFlag();
        recreateSwapchain();
        return;
    }
    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }
}

void FirstApp::recreateSwapchain()
{
    auto extent = efWindow.getExtent();
    while (extent.width == 0 || extent.height == 0)
    {
        extent = efWindow.getExtent();
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(efDevice.device());

    if (efSwapChain == nullptr)
    {
        efSwapChain = std::make_unique<EfSwapChain>(efDevice, extent);
    }
    else
    {
        efSwapChain = std::make_unique<EfSwapChain>(efDevice, extent, std::move(efSwapChain));
        if (efSwapChain->imageCount() != commandBuffers.size())
        {
            freeCommandBuffers();
            createCommandBuffers();
        }
    }

    
    createPipeline();

}

void FirstApp::loadModels()
{
    std::vector<EfModel::Vertex> vertices{
        {{0.0f, -0.5f}, {1.0f, 0, 0}},
        {{0.5f, 0.5f}, {0.0f, 1.0f, 0}},
        {{-0.5f, 0.5f}, {0.0f, 0, 1.0f}} };
    efModel = std::make_unique<EfModel>(efDevice, vertices);

    //std::vector<EfModel::Vertex> vertices{};
    //sierpinski(vertices, 10, { -1.f, 1.f }, { 1.f, 1.f }, { 0.0f, -1.f });
    
    efModel = std::make_unique<EfModel>(efDevice, vertices);
}


void FirstApp::sierpinski(
    std::vector<EfModel::Vertex>& vertices,
    int depth,
    glm::vec2 left,
    glm::vec2 right,
    glm::vec2 top)
{
    if (depth <= 0) {
        vertices.push_back({ top });
        vertices.push_back({ right });
        vertices.push_back({ left });
    }
    else {
        auto leftTop = 0.5f * (left + top);
        auto rightTop = 0.5f * (right + top);
        auto leftRight = 0.5f * (left + right);
        sierpinski(vertices, depth - 1, left, leftRight, leftTop);
        sierpinski(vertices, depth - 1, leftRight, right, rightTop);
        sierpinski(vertices, depth - 1, leftTop, rightTop, top);
    }
}

}

