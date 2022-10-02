#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

/*

	Display Jobs:

	- Initialize GLFW
	- Create a window
	- Initialize GLAD

*/

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

class Display {
public:
	Display(int, int, std::string);
	~Display();

	void Init();

	GLFWwindow* GetWindow() { return mWindow; }
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
	std::string GetTitle() { return mTitle; }
private:
	GLFWwindow* mWindow;
	int mWidth, mHeight;
	std::string mTitle;
};
