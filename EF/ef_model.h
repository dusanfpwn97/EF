#pragma once

#include "ef_device.h"
#include "glm/glm.hpp"
#include <vector>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE



namespace ef
{
class EfModel
{
public:

	struct Vertex {
		glm::vec2 position;
		glm::vec3 color;
		static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
		static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
	};

	EfModel(EfDevice& device, const std::vector<Vertex>& vertices);
	~EfModel();

	EfModel(const EfModel&) = delete;
	EfModel& operator=(const EfModel&) = delete;




	void bind(VkCommandBuffer commandBuffer);
	void draw(VkCommandBuffer commandBuffer);
private:
	void createVertexBuffers(const std::vector<Vertex>& vertices);

	EfDevice& efDevice;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	uint32_t vertexCount;
};
}