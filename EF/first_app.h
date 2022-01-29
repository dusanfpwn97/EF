#pragma once

#include "ef_window.h"
#include "ef_pipeline.h"
#include "ef_swap_chain.h"
#include "ef_device.h"
#include "ef_model.h"


#include <memory>
#include <vector>



namespace ef
{
class FirstApp {
public:
	static constexpr int WIDTH = 800;
	static constexpr int HEIGHT = 600;

	FirstApp();
	~FirstApp();

	FirstApp(const FirstApp&) = delete;
	FirstApp& operator=(const FirstApp&) = delete;

	void run();

private:
	void loadModels();
	void createPipelineLayout();
	void createPipeline();
	void createCommandBuffers();
	void freeCommandBuffers();
	void drawFrame();
	void recreateSwapchain();
	void recordCommandBuffer(int imageIndex);
	EfWindow efWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
	EfDevice efDevice{ efWindow };
	std::unique_ptr<EfSwapChain> efSwapChain;
	std::unique_ptr<EfPipeline> efPipeline;
	VkPipelineLayout pipelineLayout;
	std::vector<VkCommandBuffer> commandBuffers;
	std::unique_ptr<EfModel> efModel;

	void sierpinski(std::vector<EfModel::Vertex>& vertices, int depth, glm::vec2 left, glm::vec2 right, glm::vec2 top);
};
}