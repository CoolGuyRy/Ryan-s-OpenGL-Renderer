#include "Display.h"

Display::Display(int width, int height, std::string title) : mWindow(0), mWidth(width), mHeight(height), mTitle(title) {
	Init();
}

Display::~Display() {
	glfwTerminate();
}

void Display::Init() {

	if (!glfwInit()) {
		std::cout << "Error: Failed to initialize GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), NULL, NULL);
	if (!mWindow) {
		std::cout << "Error: Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Error: Failed to initialize OpenGL context" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(mWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSwapInterval(1);
}