#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <string>


namespace ef {
class EfWindow {
public:
	EfWindow(int w, int h, std::string name);
	~EfWindow();

	EfWindow(const EfWindow&) = delete;
	EfWindow& operator=(const EfWindow&) = delete;

	bool shouldClose() { return glfwWindowShouldClose(window); }

	VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

	void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
private:
	void initWindow();

	const int width;
	const int height;

	std::string windowName;
	GLFWwindow* window;
};
}