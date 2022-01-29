#include "ef_window.h"
#include "stdexcept"


namespace ef {
EfWindow::EfWindow(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {

	initWindow();
}

EfWindow::~EfWindow() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void ef::EfWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
{
	if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create window surface");
	}
}

void EfWindow::initWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}
}