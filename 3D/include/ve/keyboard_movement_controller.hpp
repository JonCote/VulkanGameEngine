#pragma once

#include "ve_game_object.hpp"
#include "ve_window.hpp"

namespace ve {
	class KeyboardMovementController {
	public:
		struct KeyMappings {
			int moveLeft = GLFW_KEY_A;
			int moveRight = GLFW_KEY_D;
			int moveForward = GLFW_KEY_W;
			int moveBackward = GLFW_KEY_S;

			int moveUp = GLFW_KEY_E;
			int moveDown = GLFW_KEY_Q;
			int rotateLeft = GLFW_KEY_LEFT;
			int rotateRight = GLFW_KEY_RIGHT;
			int rotateUp = GLFW_KEY_UP;
			int rotateDown = GLFW_KEY_DOWN;
		};

		void moveInPlaneXZ(GLFWwindow* window, float dt, VeGameObject& gameObject);

		KeyMappings keys{};
		float movementSpeed{ 3.f };
		float lookSpeed{ 1.5f };

	private:
		
	};
} // namespace ve