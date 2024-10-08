#include "ve/ve_model.hpp"

// std
#include <cassert>
#include <cstring>

namespace ve {

	VeModel::VeModel(VeDevice& device, const std::vector<Vertex>& vertices) : veDevice{ device } {
		createVertexBuffers(vertices);
	}

	VeModel::~VeModel() {
		vkDestroyBuffer(veDevice.device(), vertexBuffer, nullptr);
		vkFreeMemory(veDevice.device(), vertexBufferMemory, nullptr);
	}

	void VeModel::bind(VkCommandBuffer commandBuffer) {
		VkBuffer buffers[] = { vertexBuffer };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
	}

	void VeModel::draw(VkCommandBuffer commandBuffer) {
		vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
	}

	void VeModel::createVertexBuffers(const std::vector<Vertex>& vertices) {
		vertexCount = static_cast<uint32_t>(vertices.size());
			assert(vertexCount >= 3 && "Vertex count must be at least 3");
		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		veDevice.createBuffer(
			bufferSize,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			stagingBuffer,
			stagingBufferMemory);

		void* data;
		vkMapMemory(veDevice.device(), stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
		vkUnmapMemory(veDevice.device(), stagingBufferMemory);

		veDevice.createBuffer(
			bufferSize,
			VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			vertexBuffer,
			vertexBufferMemory);

		veDevice.copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

		vkDestroyBuffer(veDevice.device(), stagingBuffer, nullptr);
		vkFreeMemory(veDevice.device(), stagingBufferMemory, nullptr);
	}


	std::vector<VkVertexInputBindingDescription> VeModel::Vertex::getBindingDescriptions() {
		std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
		bindingDescriptions[0].binding = 0;
		bindingDescriptions[0].stride = sizeof(Vertex);
		bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescriptions;
	}

	std::vector<VkVertexInputAttributeDescription> VeModel::Vertex::getAttributeDescriptions() {
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, position);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}
}