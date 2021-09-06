#include "glfw3.h"
#include "Engine2d.h"

#if DEBUG == 1
	#include <vector>
	#include <iostream>
	#include <algorithm>	
	#include <string>
	#include <sstream>

	// void __attribute__((constructor)) onStart();
	void __attribute__((destructor)) Engine2d::onExit();

	void* operator new(size_t size) {
		void* p = malloc(size);
		++Engine2d::allocations;
		return p;
	}

	void operator delete(void *p) {
		free(p);
		--Engine2d::allocations;
	}

	void operator delete[](void *p) {
		free(p);
		--Engine2d::allocations;
	}

	namespace Engine2d {
		// GLFW leaks _at least_ 59 allocations
		unsigned int allocations = 0;
		void onExit() {
			std::cout << "\n";
			std::cout << "|--------------------------------------------|\n";
			std::cout << "|  Number of allocations in cosmic ether: " << Engine2d::allocations << " |\n";
			std::cout << "| -- GLFW leaks _at least_ 59 allocations -- |\n";
			std::cout << "|--------------------------------------------|\n";
		}
	}
#endif

namespace Engine2d {
	unsigned int W_WIDTH = 1280;
	unsigned int W_HEIGHT = 800;
	GLFWwindow *window;
}

int Engine2d::initWindow() {
	/* Initialize the library */
	if (!glfwInit())
		return 0;

	/* Create a windowed mode window and its OpenGL context */
	Engine2d::window = glfwCreateWindow(Engine2d::W_WIDTH, Engine2d::W_HEIGHT, "Physics engine", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return 0;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(Engine2d::window);
	glfwSwapInterval(1);

	/* Define view size as W_WIDTH and W_HEIGHT instead of -1 to 1 (also scaling and rotation) */
	glViewport(0.0f, 0.0f, Engine2d::W_WIDTH, Engine2d::W_HEIGHT);
	glLoadIdentity();
	glOrtho(0, Engine2d::W_WIDTH, 0, Engine2d::W_HEIGHT, 0, 1); //Screen size, rotation and scaling

	return 1;
}