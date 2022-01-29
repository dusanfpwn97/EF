#pragma once

#include "ef_device.h"
#include <string>
#include <vector>

namespace ef {

	struct PipelineConfigInfo
	{

	};
class EfPipeline
{
public:
	EfPipeline(EfDevice& device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo);
	~EfPipeline();

	EfPipeline(const EfPipeline&) = delete;
	void operator=(const EfPipeline&) = delete;

	static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

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