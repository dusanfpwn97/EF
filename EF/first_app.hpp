#pragma once
#include "device.hpp"
#include "game_object.hpp"
#include "renderer.hpp"
#include "window.hpp"
#include "descriptors.hpp"


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

		// Order of declarations matter!
		std::unique_ptr<DescriptorPool> globalPool{};
		GameObject::Map gameObjects;
	};
	//std::unique_ptr<Model> createCubeModel(Device& device, glm::vec3 offset);
}// namespace ef