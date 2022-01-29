#include "first_app.h"
#include <stdexcept>
#include <array>



namespace ef
{

FirstApp::FirstApp() {
    loadModels();
    createPipelineLayout();
    createPipeline();
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
    PipelineConfigInfo pipelineConfig{};
    EfPipeline::defaultPipelineConfigInfo(pipelineConfig, efSwapChain.width(), efSwapChain.height());

    pipelineConfig.renderPass = efSwapChain.getRenderPass();
    pipelineConfig.pipelineLayout = pipelineLayout;
    efPipeline = std::make_unique<EfPipeline>(
        efDevice,
        "shaders/simple_shader.vert.spv",
        "shaders/simple_shader.frag.spv",
        pipelineConfig);
}

void FirstApp::createCommandBuffers() {
    commandBuffers.resize(efSwapChain.imageCount());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = efDevice.getCommandPool();
    allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

    if (vkAllocateCommandBuffers(efDevice.device(), &allocInfo, commandBuffers.data()) !=
        VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }

    for (int i = 0; i < commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = efSwapChain.getRenderPass();
        renderPassInfo.framebuffer = efSwapChain.getFrameBuffer(i);

        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = efSwapChain.getSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
        clearValues[1].depthStencil = { 1.0f, 0 };
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        efPipeline->bind(commandBuffers[i]);
        efModel->bind(commandBuffers[i]);
        efModel->draw(commandBuffers[i]);


        vkCmdEndRenderPass(commandBuffers[i]);
        if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }
    }
}
void FirstApp::drawFrame() {
    uint32_t imageIndex;
    auto result = efSwapChain.acquireNextImage(&imageIndex);
    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    result = efSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }
}


void FirstApp::loadModels()
{
    std::vector<EfModel::Vertex> vertices{ {{0.0f, -0.5f}}, {{0.5f, 0.5f}}, {{-0.5f, 0.5f}} };
    efModel = std::make_unique<EfModel>(efDevice, vertices);

    efModel = std::make_unique<EfModel>(efDevice, vertices);
}


}