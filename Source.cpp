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

	Camera gCamera(gDisplay.GetWindow(), glm::vec3(-3.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)gDisplay.GetWidth() / (float)gDisplay.GetHeight(), 0.1f, 100.0f);
	
	Mesh* CandleMesh = new Mesh("Data/Models/cube.obj");
	Texture* CandleTexture = new Texture("Data/Textures/container2.png");
	
	Mesh* BunnyMesh = new Mesh("Data/Models/Bunny.obj");
	Texture* BunnyTexture = new Texture("Data/Textures/Bunny.jpg");
	
	Shader* CubeShader = new Shader("Data/Shaders/shaded.vert", "Data/Shaders/shaded.frag");
	Shader* LightShader = new Shader("Data/Shaders/light_source.vert", "Data/Shaders/light_source.frag");
	
	Model cube(&gCamera, projection, BunnyMesh, BunnyTexture, CubeShader, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, glm::radians(45.0f), 0.0f), glm::vec3(0.25f));
	Model light(&gCamera, projection, CandleMesh, CandleTexture, LightShader, glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.0f), glm::vec3(0.05f));
	
	float deltaTime = 0.0f, lastFrame = 0.0f;
	while (!glfwWindowShouldClose(gDisplay.GetWindow())) {
		glfwPollEvents();

		glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.09, 0.22, 0.34, 1.0)));
		glClearBufferfv(GL_DEPTH, 0, glm::value_ptr(glm::vec4(1.0)));

		if (glfwGetKey(gDisplay.GetWindow(), GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(gDisplay.GetWindow(), GL_TRUE);
		gCamera.Update(deltaTime);
		
		cube.UpdateRotation(glm::vec3(0.0f, sinf((float)glfwGetTime() * 0.005f) * 365.0f, 0.0f));

		cube.Draw();
		light.Draw();
		
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwSwapBuffers(gDisplay.GetWindow());
	}
	
	return 0;
}