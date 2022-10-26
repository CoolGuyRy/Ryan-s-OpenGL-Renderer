#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "Display.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Light.h"

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

void PrintLightDetails(Light* l) {
	switch (l->GetType()) {
		case LightType::DEFAULT:
			std::cout << "Default Light | Size: " << sizeof(*l) << std::endl;
			std::cout << "Ambient: " << l->GetAmbient().x << ", " << l->GetAmbient().y << ", " << l->GetAmbient().z << std::endl;
			std::cout << "Diffuse: " << l->GetDiffuse().x << ", " << l->GetDiffuse().y << ", " << l->GetDiffuse().z << std::endl;
			std::cout << "Specular: " << l->GetSpecular().x << ", " << l->GetSpecular().y << ", " << l->GetSpecular().z << std::endl;
			break;
		case LightType::DIRECTION:
			std::cout << "Direction Light | Size: " << sizeof(*l) << std::endl;
			std::cout << "Ambient: " << l->GetAmbient().x << ", " << l->GetAmbient().y << ", " << l->GetAmbient().z << std::endl;
			std::cout << "Diffuse: " << l->GetDiffuse().x << ", " << l->GetDiffuse().y << ", " << l->GetDiffuse().z << std::endl;
			std::cout << "Specular: " << l->GetSpecular().x << ", " << l->GetSpecular().y << ", " << l->GetSpecular().z << std::endl;
			std::cout << "Direction: " << dynamic_cast<DirectionalLight*>(l)->GetDirection().x << ", " << dynamic_cast<DirectionalLight*>(l)->GetDirection().y << ", " << dynamic_cast<DirectionalLight*>(l)->GetDirection().z << std::endl;
			break;
	}
}

int main() {
	srand((unsigned)time(NULL));
	//Display gDisplay("OpenGL Renderer");
	Display gDisplay(1280, 960, "OpenGL Renderer");

	WindowSetup(gDisplay);

	Camera gCamera(gDisplay.GetWindow(), glm::vec3(-3.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)gDisplay.GetWidth() / (float)gDisplay.GetHeight(), 0.1f, 100.0f);

	Shader* kayShader = new Shader("Data/Shaders/KayKit.vert", "Data/Shaders/KayKit.frag");

	Model gModel1(&gCamera, projection, "Data/Models/Dungeon/fbx/character_mage.fbx", kayShader, glm::vec3(-2.0, 0.0, 0.0));
	Model gModel2(&gCamera, projection, "Data/Models/Dungeon/fbx/character_knight.fbx", kayShader, glm::vec3(2.0, 0.0, 0.0));
	Model gModel3(&gCamera, projection, "Data/Models/Dungeon/fbx/character_barbarian.fbx", kayShader, glm::vec3(0.0, 0.0, 2.0));
	Model gModel4(&gCamera, projection, "Data/Models/Dungeon/fbx/character_rogue.fbx", kayShader, glm::vec3(0.0, 0.0, -2.0));

	std::vector<Light*> gLights;

	gLights.push_back(new DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(1.0, 1.0, 1.0)));
	gLights.push_back(new Light());

	for (Light* l : gLights) {
		PrintLightDetails(l);
		std::cout << std::endl;
	}

	float deltaTime = 0.0f, lastFrame = 0.0f;
	while (!glfwWindowShouldClose(gDisplay.GetWindow())) {
		glfwPollEvents();

		glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.09, 0.22, 0.34, 1.0)));
		glClearBufferfv(GL_DEPTH, 0, glm::value_ptr(glm::vec4(1.0)));

		if (glfwGetKey(gDisplay.GetWindow(), GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(gDisplay.GetWindow(), GL_TRUE);
		gCamera.Update(deltaTime);

		glm::vec3 rot(0.0f, sinf(glfwGetTime() * 0.01f) * 365.0f, 0.0f);

		//gModel1.UpdateRotation(rot);
		gModel2.UpdateRotation(-rot);
		gModel3.UpdateRotation(rot);
		gModel4.UpdateRotation(-rot);

		//gModel1.Draw();
		gModel2.Draw();
		gModel3.Draw();
		gModel4.Draw();

		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwSwapBuffers(gDisplay.GetWindow());
	}
	
	return 0;
}