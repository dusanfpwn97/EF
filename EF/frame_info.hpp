#pragma once

#include "camera.hpp"

// lib
#include <vulkan/vulkan.h>

namespace ef {
	struct FrameInfo {
		int frameIndex;
		float frameTime;
		VkCommandBuffer commandBuffer;
		Camera& camera;
		VkDescriptorSet globalDescriptorSet;
	};
}  // namespace ef