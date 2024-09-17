#pragma once

#include "ve/ve_camera.hpp"
#include "ve/ve_pipeline.hpp"
#include "ve/ve_device.hpp"
#include "ve/ve_game_object.hpp"
#include "ve/ve_frame_info.hpp"

//std
#include <memory>
#include <vector>

namespace ve {
	class SimpleRenderSystem {
	public:

		SimpleRenderSystem(VeDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
		~SimpleRenderSystem();

		SimpleRenderSystem(const SimpleRenderSystem&) = delete;
		SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

		void renderGameObjects(FrameInfo& frameInfo, std::vector<VeGameObject>& gameObjects);

	private:
		void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
		void createPipeline(VkRenderPass renderPass);
		

		VeDevice& veDevice;

		std::unique_ptr<VePipeline> vePipeline;
		VkPipelineLayout pipelineLayout;
	};
} // namespace ve