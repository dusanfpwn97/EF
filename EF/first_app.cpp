#include "first_app.hpp"
#include "keyboard_movement_controller.hpp"
#include "render_system.hpp"
#include "camera.hpp"
// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <array>
#include <cassert>
#include <stdexcept>
#include <chrono>

namespace ef {

    FirstApp::FirstApp() {
        loadGameObjects();
    }

    FirstApp::~FirstApp() {}

    void FirstApp::run() {
        RenderSystem simpleRenderSystem{ device, renderer.getSwapChainRenderPass() };
        Camera camera{};


        camera.setViewTarget(glm::vec3(-1.f, -2.f, 2.f), glm::vec3(0.0f, 0.f, 2.5f));

        auto viewerObject = GameObject::createGameObject();
        KeyboardMovementController cameraController{};


        auto currentTime = std::chrono::high_resolution_clock::now();


        while (!window.shouldClose()) {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();


            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();

            frameTime = glm::min(frameTime, 1.f); //max frame time (like 0.4 in unreal)
            currentTime = newTime;

            cameraController.moveInPlaneXZ(window.getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);
            float aspect = renderer.getAspectRatio();

            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 100.f);
            if (auto commandBuffer = renderer.beginFrame()) {
                renderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
                renderer.endSwapChainRenderPass(commandBuffer);
                renderer.endFrame();
            }
        }

        vkDeviceWaitIdle(device.device());
    }

    void FirstApp::loadGameObjects() {
        std::shared_ptr<Model> model = Model::createModelFromFile(device, "C:/Users/dusan/source/repos/EF/EF/Models/smooth_vase.obj");

        auto cube = GameObject::createGameObject();
        cube.model = model;
        cube.transform.translation = { .0f, .0f, 2.5f };
        cube.transform.scale = glm::vec3{ 3.f };

        gameObjects.push_back(std::move(cube));
    }


}// namespace ef