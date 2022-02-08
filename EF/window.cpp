#include "window.hpp"
#include "stdexcept"


namespace ef {
EfWindow::EfWindow(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {

	initWindow();
}

EfWindow::~EfWindow() {

	SDL_DestroyWindow(window);

}

bool EfWindow::shouldClose()
{
	/*
	SDL_Event event;
	while (SDL_PollEvent(&event)) {  // poll until all events are handled!
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
		{
			return true;
		}
	}
	*/
	return false;
}

void ef::EfWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
{
	SDL_Vulkan_CreateSurface(window, instance, surface);
		/*
	//&&
	if (!SDL_Vulkan_CreateSurface(window, instance, surface))
	{
		throw std::runtime_error("failed to create window surface");
	}*/
}void EfWindow::initWindow() {
	SDL_Init(SDL_INIT_VIDEO);

	Uint32 flags = SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE;

	//SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN);

	//create blank SDL window for our application
	window = SDL_CreateWindow(
		"Vulkan Engine", //window title
		SDL_WINDOWPOS_UNDEFINED, //window position x (don't care)
		SDL_WINDOWPOS_UNDEFINED, //window position y (don't care)
		width,  //window width in pixels
		height, //window height in pixels
		flags
	);
}


void EfWindow::framebufferResizeCallback(SDL_Window* sdlWindow, int width, int height)
{
	//auto efWindow = reinterpret_cast<EfWindow*>(glfwGetWindowUserPointer(window));
	// TODO check if this is good
	auto efWindow = reinterpret_cast<EfWindow*>(sdlWindow);
	efWindow->framebufferResized = true;
	efWindow->width = width;
	efWindow->height = height;

}


}