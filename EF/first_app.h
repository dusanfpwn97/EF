#pragma once

#include "ef_window.h"
#include "ef_pipeline.h"
#include "ef_device.h"

class FirstApp {
public:
	static constexpr int WIDTH = 800;
	static constexpr int HEIGHT = 600;

	void run();

private:
	ef::EfWindow efWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
	ef::EfDevice efDevice{ efWindow };
	ef::EfPipeline efPipeline{efDevice, "Shaders/simple_shader.vert.spv", "Shaders/simple_shader.frag.spv", ef::EfPipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT) };
};
