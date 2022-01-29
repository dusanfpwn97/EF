#pragma once

#include "ef_device.h"
#include "ef_model.h"
#include <string>
#include <vector>



namespace ef {

	struct PipelineConfigInfo
	{
		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

class EfPipeline
{
public:
	EfPipeline(EfDevice& device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo);
	~EfPipeline();

	EfPipeline(const EfPipeline&) = delete;
	void operator=(const EfPipeline&) = delete;

	void bind(VkCommandBuffer commandBuffer);
	static PipelineConfigInfo defaultPipelineConfigInfo(PipelineConfigInfo& configInfo, uint32_t width, uint32_t height);

private:
	static std::vector<char> readFile(const std::string& filePath);

	void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo);

	void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

	EfDevice& efDevice;
	VkPipeline graphicsPipeline;
	VkShaderModule vertShaderModule;
	VkShaderModule fragShaderModule;

};
}