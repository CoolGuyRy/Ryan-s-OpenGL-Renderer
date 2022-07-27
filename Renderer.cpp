#include "Renderer.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

Renderer::Renderer(unsigned width, unsigned height) {
	mWindow = 0;
	mTime = 0;
	mWidth = width;
	mHeight = height;
}

Renderer::~Renderer() {
	glfwTerminate();
}

void Renderer::Init() {
	if (!glfwInit()) {
		std::cout << "Error: Failed to initialize GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(mWidth, mHeight, "Renderer", NULL, NULL);
	if (!mWindow) {
		std::cout << "Error: Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(mWindow);

	glfwSetKeyCallback(mWindow, KeyCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Error: Failed to initialize GLAD" << std::endl;
		return;
	}

	stbi_set_flip_vertically_on_load(true);
}

void Renderer::Run() {
	while (!glfwWindowShouldClose(mWindow)) {
		Input();

		Update(mTime);

		Render();

		mTime = glfwGetTime();
	}
}

void Renderer::Input() {
	
}

void Renderer::Update(float time) {
	
}

void Renderer::Render() {
	glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
	glClearBufferfv(GL_DEPTH, 0, glm::value_ptr(glm::vec4(1.0f)));

	// Draw

	glfwSwapBuffers(mWindow);
}