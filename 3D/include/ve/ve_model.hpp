#pragma once

#include "ve_device.hpp"
#include "ve_buffer.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

// std
#include <vector>
#include <string>
#include <memory>


namespace ve {
	class VeModel {
	public:

		struct Vertex {
			glm::vec3 position{};
			glm::vec3 color{};
			glm::vec3 normal{};
			glm::vec2 uv{};

			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

			bool operator==(const Vertex& other) const {
				return position == other.position && color == other.color && normal == other.normal && uv == other.uv;
			}
		};

		struct Builder {
			std::vector<Vertex> vertices{};
			std::vector<uint32_t> indices{};

			void loadModel(const std::string& filePath);
		};

		VeModel(VeDevice& device, const VeModel::Builder& builder);
		~VeModel();

		VeModel(const VeModel&) = delete;
		VeModel& operator=(const VeModel&) = delete;

		static std::unique_ptr<VeModel> createModelFromFile(VeDevice& device, const std::string& filePath);

		void bind(VkCommandBuffer commandBuffer);
		void draw(VkCommandBuffer commandBuffer);

	private:
		void createVertexBuffers(const std::vector<Vertex>& vertices);
		void createIndexBuffers(const std::vector<uint32_t>& indices);

		VeDevice& veDevice;

		std::unique_ptr<VeBuffer> vertexBuffer;
		uint32_t vertexCount;

		bool hasIndexBuffer{ false };
		std::unique_ptr<VeBuffer> indexBuffer;
		uint32_t indexCount;
	};
} // namespace ve