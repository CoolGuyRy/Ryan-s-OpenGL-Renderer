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
		case LightType::DIRECTION:
			std::cout << "Direction Light | Size: " << sizeof(*l) << std::endl;
			std::cout << "Ambient: " << l->GetAmbient().x << ", " << l->GetAmbient().y << ", " << l->GetAmbient().z << std::endl;
			std::cout << "Diffuse: " << l->GetDiffuse().x << ", " << l->GetDiffuse().y << ", " << l->GetDiffuse().z << std::endl;
			std::cout << "Specular: " << l->GetSpecular().x << ", " << l->GetSpecular().y << ", " << l->GetSpecular().z << std::endl;
			std::cout << "Direction: " << dynamic_cast<DirectionalLight*>(l)->GetDirection().x << ", " << dynamic_cast<DirectionalLight*>(l)->GetDirection().y << ", " << dynamic_cast<DirectionalLight*>(l)->GetDirection().z << std::endl;
			break;
		case LightType::POINT:
			std::cout << "Point Light | Size: " << sizeof(*l) << std::endl;
			std::cout << "Ambient: " << l->GetAmbient().x << ", " << l->GetAmbient().y << ", " << l->GetAmbient().z << std::endl;
			std::cout << "Diffuse: " << l->GetDiffuse().x << ", " << l->GetDiffuse().y << ", " << l->GetDiffuse().z << std::endl;
			std::cout << "Specular: " << l->GetSpecular().x << ", " << l->GetSpecular().y << ", " << l->GetSpecular().z << std::endl;
			std::cout << "Position: " << dynamic_cast<PointLight*>(l)->GetPosition().x << ", " << dynamic_cast<PointLight*>(l)->GetPosition().y << ", " << dynamic_cast<PointLight*>(l)->GetPosition().z << std::endl;
			break;
	}
}

int main() {
	srand((unsigned)time(NULL));
	Display gDisplay("OpenGL Renderer");
	//Display gDisplay(1280, 960, "OpenGL Renderer");

	WindowSetup(gDisplay);

	Camera gCamera(gDisplay.GetWindow(), glm::vec3(-3.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(90.0f), (float)gDisplay.GetWidth() / (float)gDisplay.GetHeight(), 0.1f, 100.0f);

	Shader* kayShader = new Shader("Data/Shaders/KayKit.vert", "Data/Shaders/KayKit.frag");

	"Data/Models/Dungeon/fbx/wallIntersection.fbx";

	std::vector<Model*> gScene;

	for (unsigned i = 0; i < 10; i++) {
		for (unsigned j = 0; j < 10; j++) {
			for (unsigned k = 0; k < 1; k++) {
				Model* m = new Model(&gCamera, projection, "Data/Models/Dungeon/fbx/wallIntersection.fbx", kayShader);
				m->UpdatePosition(glm::vec3(i * 6.0f, k * 4.0f, j * 6.0f));
				gScene.push_back(m);
			}
		}
	}

	float deltaTime = 0.0f, lastFrame = 0.0f;
	while (!glfwWindowShouldClose(gDisplay.GetWindow())) {
		glfwPollEvents();

		glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.09, 0.22, 0.34, 1.0)));
		glClearBufferfv(GL_DEPTH, 0, glm::value_ptr(glm::vec4(1.0)));

		if (glfwGetKey(gDisplay.GetWindow(), GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(gDisplay.GetWindow(), GL_TRUE);
		gCamera.Update(deltaTime);
		
		for (unsigned i = 0; i < gScene.size(); i++) {
			gScene[i]->Draw();
		}

		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwSwapBuffers(gDisplay.GetWindow());
	}
	
	return 0;
}