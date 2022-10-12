#include "Display.h"

Display::Display(std::string title) : mWindow(0), mWidth(-1), mHeight(-1), mTitle(title) {
	if (!glfwInit()) {
		std::cout << "Error: Failed to initialize GLFW" << std::endl;
		return;
	}
	
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	mWidth = mode->width;
	mHeight = mode->height;
	
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), glfwGetPrimaryMonitor(), NULL);
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

	glViewport(0, 0, mWidth, mHeight);

	LogContextInfo();

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(mWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glfwSetWindowPos(mWindow, mode->width / 2 - mWidth / 2, mode->height / 2 - mHeight / 2);

	glfwSwapInterval(1);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

Display::Display(int width, int height, std::string title) : mWindow(0), mWidth(width), mHeight(height), mTitle(title) {
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

	glViewport(0, 0, mWidth, mHeight);

	LogContextInfo();

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(mWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(mWindow, mode->width / 2 - mWidth / 2, mode->height / 2 - mHeight / 2);

	glfwSwapInterval(1);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

Display::~Display() {
	glfwTerminate();
}

void Display::LogContextInfo() {
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
}