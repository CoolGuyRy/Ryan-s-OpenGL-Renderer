#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "Display.h"

struct InputContainer {
	int W = GLFW_RELEASE;
	int A = GLFW_RELEASE;
	int S = GLFW_RELEASE;
	int D = GLFW_RELEASE;
	int SPACE = GLFW_RELEASE;
	int ESCAPE = GLFW_RELEASE;
	
	int MOUSE_LEFT = GLFW_RELEASE;
	int MOUSE_RIGHT = GLFW_RELEASE;
	int MOUSE_MIDDLE = GLFW_RELEASE;
	
	double MOUSE_X = 0;
	double MOUSE_Y = 0;
	double MOUSE_SCROLL = 0;
} gInput;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_W:
		if (action == GLFW_PRESS)
			gInput.W = GLFW_PRESS;
		else if (action == GLFW_RELEASE)
			gInput.W = GLFW_RELEASE;
		break;
	case GLFW_KEY_A:
		if (action == GLFW_PRESS)
			gInput.A = GLFW_PRESS;
		else if (action == GLFW_RELEASE)
			gInput.A = GLFW_RELEASE;
		break;
	case GLFW_KEY_S:
		if (action == GLFW_PRESS)
			gInput.S = GLFW_PRESS;
		else if (action == GLFW_RELEASE)
			gInput.S = GLFW_RELEASE;
		break;
	case GLFW_KEY_D:
		if (action == GLFW_PRESS)
			gInput.D = GLFW_PRESS;
		else if (action == GLFW_RELEASE)
			gInput.D = GLFW_RELEASE;
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
	// std::cout << "Key: " << key << " Action: " << action << std::endl;
}
void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	gInput.MOUSE_X = xpos;
	gInput.MOUSE_Y = ypos;
	// std::cout << "X: " << xpos << " Y: " << ypos << std::endl;
}
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			gInput.MOUSE_LEFT = action;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			gInput.MOUSE_RIGHT = action;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			gInput.MOUSE_MIDDLE = action;
			break;
		default:
			break;
	}
	// std::cout << "Mouse Button: " << button << " Action: " << action << std::endl;
}
void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	gInput.MOUSE_SCROLL = yoffset;
	// std::cout << "Mouse Scroll: " << xoffset << ", " << yoffset << std::endl;
}
void ErrorCallback(int error, const char* description) {
	std::cout << "Error " << error << ": " << description << std::endl;
}

int main() {
	Display gDisplay(1280, 960, "OpenGL Renderer");

	glfwSetErrorCallback(ErrorCallback);
	glfwSetKeyCallback(gDisplay.GetWindow(), KeyCallback);
	glfwSetCursorPosCallback(gDisplay.GetWindow(), CursorPositionCallback);
	glfwSetMouseButtonCallback(gDisplay.GetWindow(), MouseButtonCallback);
	glfwSetScrollCallback(gDisplay.GetWindow(), MouseScrollCallback);

	while (!glfwWindowShouldClose(gDisplay.GetWindow())) {
		glfwPollEvents();

		glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.09, 0.22, 0.34, 1.0)));
		glClearBufferfv(GL_DEPTH, 0, glm::value_ptr(glm::vec4(1.0)));
		
		glfwSwapBuffers(gDisplay.GetWindow());
	}
	
	return 0;
}