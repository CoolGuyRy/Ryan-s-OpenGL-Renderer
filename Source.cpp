#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "Display.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	
}
void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {

}
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	
}
void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {

}
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void ErrorCallback(int error, const char* description) {
	std::cout << "Error " << error << ": " << description << std::endl;
}
void WindowSetup(Display& d) {
	glfwSetErrorCallback(ErrorCallback);
	glfwSetKeyCallback(d.GetWindow(), KeyCallback);
	glfwSetCursorPosCallback(d.GetWindow(), CursorPositionCallback);
	glfwSetMouseButtonCallback(d.GetWindow(), MouseButtonCallback);
	glfwSetScrollCallback(d.GetWindow(), MouseScrollCallback);
	glfwSetFramebufferSizeCallback(d.GetWindow(), FrameBufferSizeCallback);

	stbi_set_flip_vertically_on_load(true);
}

int main() {
	srand((unsigned)time(NULL));
	//Display gDisplay("OpenGL Renderer");
	Display gDisplay(1280, 960, "OpenGL Renderer");

	WindowSetup(gDisplay);

	Camera gCamera(gDisplay.GetWindow(), glm::vec3(0.0f, 1.5f, 0.0f), glm::vec2(180.0f, 0.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)gDisplay.GetWidth() / (float)gDisplay.GetHeight(), 0.1f, 100.0f);

	//Model bModel(&gCamera, projection, new Mesh("Data/Models/efa.obj"), new Texture("Data/Textures/efa.png"), new Shader("Data/Shaders/basic.vert", "Data/Shaders/basic.frag"), glm::vec3(-5.0f, 1.5f, 0.0f), glm::vec3(glm::radians(15.0f), 0.0f, glm::radians(15.0f)), glm::vec3(0.25f));
	//Model aModel(&gCamera, projection, new Mesh("Data/Models/f22.obj"), new Texture("Data/Textures/f22.png"), new Shader("Data/Shaders/basic.vert", "Data/Shaders/basic.frag"), glm::vec3(-5.0f, 1.5f, 1.0f), glm::vec3(glm::radians(15.0f), 0.0f, glm::radians(-15.0f)), glm::vec3(0.25f));
	//Model vikingRoom(&gCamera, projection, new Mesh("Data/Models/viking_room.obj"), new Texture("Data/Textures/viking_room.png"),	 new Shader("Data/Shaders/basic.vert", "Data/Shaders/basic.frag"), glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(glm::radians(-90.0f), 0.0f, 0.0f), glm::vec3(3.0f));
	Model cube(&gCamera, projection, new Mesh("Data/Models/cube.obj"), new Texture("Data/Textures/container2.png"), new Shader("Data/Shaders/basic.vert", "Data/Shaders/basic.frag"), glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(glm::radians(-90.0f), 0.0f, 0.0f), glm::vec3(1.0f));

	float deltaTime = 0.0f, lastFrame = 0.0f;
	while (!glfwWindowShouldClose(gDisplay.GetWindow())) {
		glfwPollEvents();

		glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.09, 0.22, 0.34, 1.0)));
		glClearBufferfv(GL_DEPTH, 0, glm::value_ptr(glm::vec4(1.0)));

		if (glfwGetKey(gDisplay.GetWindow(), GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(gDisplay.GetWindow(), GL_TRUE);
		gCamera.Update(deltaTime);

		cube.Draw();
		
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwSwapBuffers(gDisplay.GetWindow());
	}
	
	return 0;
}