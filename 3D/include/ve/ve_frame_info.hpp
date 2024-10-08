#pragma once

#include "ve_camera.hpp"
#include "ve_game_object.hpp"

// lib
#include <vulkan/vulkan.h>


namespace ve {

	#define MAX_LIGHTS 10

	struct PointLight {
		glm::vec4 position{};
		glm::vec4 color{};
	};

	struct GlobalUbo {
		glm::mat4 projection{ 1.f };
		glm::mat4 view{ 1.f };
		glm::vec4 ambientLightColor{ 1.0f, 1.0f, 1.0f, 0.02f };
		PointLight pointLights[MAX_LIGHTS];
		int numLights;
	};

	struct FrameInfo {
		int frameIndex;
		float frameTime;
		VkCommandBuffer commandBuffer;
		VeCamera& camera;
		VkDescriptorSet globalDescriptorSet;
		VeGameObject::Map& gameObjects;
	};

} // namespace ve
