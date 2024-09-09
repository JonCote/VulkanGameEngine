#include "ve/first_app.hpp"
#include "ve/simple_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <stdexcept>
#include <array>
#include <cassert>

namespace ve {
	
	FirstApp::FirstApp() {
		loadGameObjects();
	}

	FirstApp::~FirstApp() {}

	void FirstApp::run() {
		SimpleRenderSystem simpleRenderSystem{ veDevice, veRenderer.getSwapChainRenderPass() };

		while (!veWindow.shouldClose()) {
			glfwPollEvents();
			
			if (auto commandBuffer = veRenderer.beginFrame()) {

				// begin offscreen shadow pass
				// render shadow casting objects
				// end offscreen shadow pass

				veRenderer.beginSwapChainRenderPass(commandBuffer);
				simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects);
				veRenderer.endSwapChainRenderPass(commandBuffer);
				veRenderer.endFrame();
			}

		}

		vkDeviceWaitIdle(veDevice.device());
	}

	void FirstApp::loadGameObjects() {
		std::vector<VeModel::Vertex> vertices{
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
		};
		auto veModel = std::make_shared<VeModel>(veDevice, vertices);

		auto triangle = VeGameObject::createGameObject();
		triangle.model = veModel;
		triangle.color = { 0.1f, 0.8f, 0.1f };
		triangle.transform2d.translation.x = 0.2f;
		triangle.transform2d.scale = { 2.f, .5f };
		triangle.transform2d.rotation = .25f * glm::two_pi<float>();

		gameObjects.push_back(std::move(triangle));
	}

}