#include <iostream>
#include "Display.h"

struct InputContainer {
	int W;
	int A;
	int S;
	int D;
	int SPACE;
	int ESCAPE;
} gInput;

void KeyCallback(GLFWwindow*, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_W:
		gInput.W = action;
		break;
	case GLFW_KEY_A:
		gInput.A = action;
		break;
	case GLFW_KEY_S:
		gInput.S = action;
		break;
	case GLFW_KEY_D:
		gInput.D = action;
		break;
	case GLFW_KEY_SPACE:
		gInput.SPACE = action;
		break;
	case GLFW_KEY_ESCAPE:
		gInput.ESCAPE = action;
		break;
	default:
		break;
	}
}
void ErrorCallback(int error, const char* description) {
	std::cout << "Error: " << description << std::endl;
}

int main() {

	Display gDisplay(1280, 960, "OpenGL Renderer");
	
	glfwSetErrorCallback(ErrorCallback);
	glfwSetKeyCallback(gDisplay.GetWindow(), KeyCallback);

	while (!glfwWindowShouldClose(gDisplay.GetWindow())) {
		if (gInput.ESCAPE == GLFW_PRESS)
			glfwSetWindowShouldClose(gDisplay.GetWindow(), GLFW_TRUE);

		glfwSwapBuffers(gDisplay.GetWindow());
		glfwPollEvents();
	}
	
	return 0;
}