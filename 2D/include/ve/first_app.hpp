#pragma once

#include "ve_window.hpp"
#include "ve_device.hpp"
#include "ve_game_object.hpp"
#include "ve_renderer.hpp"

//std
#include <memory>
#include <vector>

namespace ve {
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


		VeWindow veWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
		VeDevice veDevice{ veWindow };
		VeRenderer veRenderer{ veWindow, veDevice };

		std::vector<VeGameObject> gameObjects;
	};
} // namespace ve