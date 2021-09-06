#pragma once

#if DEBUG == 1
	#include <vector>
	#include <string>
#endif

namespace Engine2d {
	#if DEBUG == 1
		extern unsigned int allocations;
		void onExit();
	#endif

	// GLFW related initialization
	extern unsigned int W_WIDTH;
	extern unsigned int W_HEIGHT;
	extern GLFWwindow *window;
	int initWindow();
}