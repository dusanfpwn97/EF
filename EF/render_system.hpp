#pragma once

#include "device.hpp"
#include "game_object.hpp"
#include "pipeline.hpp"
#include "camera.hpp"
#include "frame_info.hpp"

// std
#include <memory>
#include <vector>

namespace ef {
	class RenderSystem {
	public:
		RenderSystem(Device& device, VkRenderPass renderPass);
		~RenderSystem();

		RenderSystem(const RenderSystem&) = delete;
		RenderSystem& operator=(const RenderSystem&) = delete;

		void renderGameObjects(FrameInfo &frameInfo, std::vector<GameObject>& gameObjects);

	private:
		void createPipelineLayout();
		void createPipeline(VkRenderPass renderPass);

		Device& device;

		std::unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout;
	};
}  // namespace ef