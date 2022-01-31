#pragma once
#include "device.hpp"
#include "game_object.hpp"
#include "renderer.hpp"
#include "window.hpp"

// std
#include <memory>
#include <vector>

namespace ef {


	class FirstApp {

	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		void run();

	private:
		void loadGameObjects();

		EfWindow window{ WIDTH, HEIGHT , "Vulkan Tutorial" };
		Device device{ window };
		Renderer renderer{ window, device };

		std::vector<GameObject> gameObjects;
	};
}// namespace ef