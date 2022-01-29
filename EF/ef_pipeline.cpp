#include "ef_pipeline.h"

#include <fstream>
#include <stdexcept>
#include <iostream>
#include "ef_device.h"
#include <cassert>


namespace ef {

EfPipeline::EfPipeline(EfDevice& device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo)
	: efDevice {device}
{
	createGraphicsPipeline(vertFilepath, fragFilepath, configInfo);
}

EfPipeline::~EfPipeline()
{
}

std::vector<char> EfPipeline::readFile(const std::string& filePath)
{
	std::ifstream file(filePath, std::ios::ate | std::ios::binary);

	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file " + filePath);
	}

	size_t fileSize = static_cast<size_t>(file.tellg());

	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;

}

PipelineConfigInfo EfPipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height)
{
	PipelineConfigInfo configInfo{};

	return configInfo;
}

void EfPipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule)
{
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	if (vkCreateShaderModule(efDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create shader module");
	}
}

void EfPipeline::createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo)
{
	auto vertCode = readFile(vertFilepath);
	auto fragCode = readFile(fragFilepath);

	std::cout << "vert " << vertCode.size() << "\n";
	std::cout << "vert " << fragCode.size() << "\n";

}
}