#include "ve/first_app.hpp"

// std
#include <iostream>
#include <cstdlib>
#include <stdexcept>


int main() {
	ve::FirstApp app{};

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}