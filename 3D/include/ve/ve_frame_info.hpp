#pragma once

#include "ve_camera.hpp"

// lib
#include <vulkan/vulkan.h>


namespace ve {

	struct FrameInfo {
		int frameIndex;
		float frameTime;
		VkCommandBuffer commandBuffer;
		VeCamera& camera;
	};

} // namespace ve
