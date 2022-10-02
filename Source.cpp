#include <iostream>
#include "Display.h"

int main() {

	Display gDisplay(1280, 960, "OpenGL Renderer");

	while (!glfwWindowShouldClose(gDisplay.GetWindow())) {

		if (gInput.ESCAPE == GLFW_PRESS) 
			glfwSetWindowShouldClose(gDisplay.GetWindow(), true);
		
		glfwSwapBuffers(gDisplay.GetWindow());
		glfwPollEvents();
	}

	glfwDestroyWindow(gDisplay.GetWindow());
	glfwTerminate();
	
	return 0;
}