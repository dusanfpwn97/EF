#pragma once

#include "window.hpp"
#include "swap_chain.hpp"
#include "device.hpp"

#include <memory>
#include <vector>
#include <cassert>

namespace ef {

	class Renderer {
	public:

		Renderer(EfWindow& window, Device& device);
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		VkRenderPass getSwapChainRenderPass() const { return efSwapChain->getRenderPass(); }
		float getAspectRatio() const { return efSwapChain->extentAspectRatio(); }
		bool isFrameInProgress() const { return isFrameStarted; }

		VkCommandBuffer getCurrentCommandBuffer() const {
			assert(isFrameStarted && "Cannot get command buffer when frame is not in progress");
			return commandBuffers[currentFrameIndex]; }
		
		int getFrameIndex() const {
			assert(isFrameStarted && "Cannot get frame index when frame not in progress");
			return currentFrameIndex;
		}


		VkCommandBuffer beginFrame();
		void endFrame();
		void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
		void endSwapChainRenderPass  (VkCommandBuffer commandBuffer);


	private:

		void createCommandBuffers();
		void freeCommandBuffers();
		void recreateSwapChain();


		EfWindow& window;
		Device& device;
		std::unique_ptr<EfSwapChain> efSwapChain;
		std::vector<VkCommandBuffer> commandBuffers;

		uint32_t currentImageIndex = 0;
		int currentFrameIndex = 0;
		bool isFrameStarted = false;
	};
}