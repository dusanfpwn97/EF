#pragma once


#include <string>
#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>
#undef main

namespace ef {
class EfWindow {
public:
	EfWindow(int w, int h, std::string name);
	~EfWindow();

	EfWindow(const EfWindow&) = delete;
	EfWindow& operator=(const EfWindow&) = delete;

	bool shouldClose();
	bool wasWindowResized() { return framebufferResized; }
	void resetWindowResizedFlag() { framebufferResized = false; }

	SDL_Window* getSDLwindow() const { return window; }
	VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

	void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
private:

	static void framebufferResizeCallback(SDL_Window* sdlWindow, int width, int height);
	void initWindow();

	int width;
	int height;

	bool framebufferResized = false;

	std::string windowName;
	SDL_Window* window;
};
}