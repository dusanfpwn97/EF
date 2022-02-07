#include "first_app.hpp"
#include "keyboard_movement_controller.hpp"
#include "render_system.hpp"
#include "camera.hpp"
#include "ef_vk_buffer.hpp"

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

    struct GlobalUbo
    {
       glm::mat4 projectionView{ 1.f };
       glm::vec4 ambientLightColor{ 1.f, 1.f, 1.f, .02f }; // w is intensity
       glm::vec3 lightPosition{ -1.0f };
       alignas(16) glm::vec4 lightColor{ 1.0f }; // w is intensity
    };



    FirstApp::FirstApp() {
        globalPool = DescriptorPool::Builder(device)
            .setMaxSets(EfSwapChain::MAX_FRAMES_IN_FLIGHT)
            .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, EfSwapChain::MAX_FRAMES_IN_FLIGHT)
            .build();

        loadGameObjects();
    }

    FirstApp::~FirstApp() {}

    void FirstApp::run() {

        std::vector<std::unique_ptr<EfVkBuffer>> uboBuffers(EfSwapChain::MAX_FRAMES_IN_FLIGHT);

        for (int i = 0; i < uboBuffers.size(); i++)
        {
            uboBuffers[i] = std::make_unique<EfVkBuffer>(
                device,
                sizeof(GlobalUbo),
                1,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

            uboBuffers[i]->map();
        }


        auto globalSetLayout = DescriptorSetLayout::Builder(device)
            .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
            .build();

        std::vector<VkDescriptorSet> globalDescriptorSets(EfSwapChain::MAX_FRAMES_IN_FLIGHT);

        for (int i = 0; i < globalDescriptorSets.size(); i++) {
            auto bufferInfo = uboBuffers[i]->descriptorInfo();
            DescriptorWriter(*globalSetLayout, *globalPool)
                .writeBuffer(0, &bufferInfo)
                .build(globalDescriptorSets[i]);
        }



        RenderSystem simpleRenderSystem{
            device,
            renderer.getSwapChainRenderPass(),
            globalSetLayout->getDescriptorSetLayout() };


        Camera camera{};


        camera.setViewTarget(glm::vec3(-1.f, -2.f, 2.f), glm::vec3(0.0f, 0.f, 2.5f));

        auto viewerObject = GameObject::createGameObject();
        viewerObject.transform.translation.z = -2.f;
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

                int frameIndex = renderer.getFrameIndex();
                FrameInfo frameInfo{ frameIndex, frameTime, commandBuffer, camera, globalDescriptorSets[frameIndex], gameObjects };
               
                
                // update
                GlobalUbo ubo{};
                ubo.projectionView = camera.getProjection() * camera.getView();
                uboBuffers[frameIndex]->writeToBuffer(&ubo);
                uboBuffers[frameIndex]->flush();


                // render
                renderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(frameInfo);
                renderer.endSwapChainRenderPass(commandBuffer);
                renderer.endFrame();
            }
        }

        vkDeviceWaitIdle(device.device());
    }

    void FirstApp::loadGameObjects() {
        std::shared_ptr<Model> model = Model::createModelFromFile(device, "C:/Users/dusan/source/repos/EF/EF/Models/flat_vase.obj");

        auto flatVase = GameObject::createGameObject();
        flatVase.model = model;
        flatVase.transform.translation = { -.5f, .5f, 0.f };
        flatVase.transform.scale = glm::vec3{ 3.f, 1.5f, 3.f };

        gameObjects.emplace(flatVase.getId(), std::move(flatVase));

        model = Model::createModelFromFile(device, "C:/Users/dusan/source/repos/EF/EF/Models/smooth_vase.obj");
        auto smoothVase = GameObject::createGameObject();
        smoothVase.model = model;
        smoothVase.transform.translation = { .5f, .5f, 0.f };
        smoothVase.transform.scale = { 3.f, 1.5f, 3.f };

        gameObjects.emplace(smoothVase.getId(), std::move(smoothVase));

        model = Model::createModelFromFile(device, "C:/Users/dusan/source/repos/EF/EF/Models/quad.obj");
        auto floor = GameObject::createGameObject();
        floor.model = model;
        floor.transform.translation = { 0.f, .5f, 0.f };
        floor.transform.scale = { 3.f, 1.f, 3.f };


        gameObjects.emplace(floor.getId(), std::move(floor));
    }


}// namespace ef