#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "Display.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Mesh.h"

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

struct Entity {
	Entity() {
		position = glm::vec3(0.0f);
		rotation = glm::vec3(0.0f);
		scale = glm::vec3(1.0f);
	}
	Entity(glm::vec3 p) {
		position = p;
		rotation = glm::vec3(0.0f);
		scale = glm::vec3(1.0f);
	}
	Entity(glm::vec3 p, glm::vec3 r) {
		position = p;
		rotation = r;
		scale = glm::vec3(1.0f);
	}
	Entity(glm::vec3 p, glm::vec3 r, glm::vec3 s) {
		position = p;
		rotation = r;
		scale = s;
	}

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 getWorldMatrix() {
		glm::mat4 result(1.0f);

		result = glm::translate(result, position);
		result = glm::rotate(result, rotation.x, glm::vec3(1.0, 0.0, 0.0));
		result = glm::rotate(result, rotation.y, glm::vec3(0.0, 1.0, 0.0));
		result = glm::rotate(result, rotation.z, glm::vec3(0.0, 0.0, 1.0));
		result = glm::scale(result, scale);

		return result;
	}
};

int main() {
	srand((unsigned)time(NULL));
	//Display gDisplay("OpenGL Renderer");
	Display gDisplay(1280, 960, "OpenGL Renderer");

	WindowSetup(gDisplay);

	Shader gShader("Data/Shaders/basic.vert", "Data/Shaders/basic.frag");
	Shader lShader("Data/Shaders/light_source.vert", "Data/Shaders/light_source.frag");

	Texture gTexture("Data/Textures/brick_diffuse.png");
	Texture hTexture("Data/Textures/happyface.png");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexture.GetTexture());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, hTexture.GetTexture());

	Mesh gMesh("Data/Models/cube.obj");

	glBindVertexArray(gMesh.GetVAO());
	glBindBuffer(GL_ARRAY_BUFFER, gMesh.GetVBO());

	GLuint CmodelLoc = glGetUniformLocation(gShader.GetProgram(), "model");
	GLuint CviewLoc = glGetUniformLocation(gShader.GetProgram(), "view");
	GLuint CprojLoc = glGetUniformLocation(gShader.GetProgram(), "proj");
	GLuint LmodelLoc = glGetUniformLocation(lShader.GetProgram(), "model");
	GLuint LviewLoc = glGetUniformLocation(lShader.GetProgram(), "view");
	GLuint LprojLoc = glGetUniformLocation(lShader.GetProgram(), "proj");

	Camera gCamera(gDisplay.GetWindow(), glm::vec3(0.0, 0.0, 20.0), glm::vec3(0.0f, 0.0f, -1.0f));

	Entity cube(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0f, 45.0f, 0.0f));
	Entity lightSource(glm::vec3(8.0, 1.0, -8.0), glm::vec3(0.0), glm::vec3(0.25));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)gDisplay.GetWidth() / (float)gDisplay.GetHeight(), 0.1f, 100.0f);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!glfwWindowShouldClose(gDisplay.GetWindow())) {
		glfwPollEvents();

		glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.09, 0.22, 0.34, 1.0)));
		glClearBufferfv(GL_DEPTH, 0, glm::value_ptr(glm::vec4(1.0)));

		if (glfwGetKey(gDisplay.GetWindow(), GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(gDisplay.GetWindow(), GL_TRUE);
		gCamera.Update(deltaTime);

		gShader.Use();

		glUniformMatrix4fv(CviewLoc, 1, GL_FALSE, glm::value_ptr(gCamera.GetViewMatrix()));
		glUniformMatrix4fv(CprojLoc, 1, GL_FALSE, glm::value_ptr(projection));
		
		glUniform1i(glGetUniformLocation(gShader.GetProgram(), "mTex"), 0);
		glUniform1i(glGetUniformLocation(gShader.GetProgram(), "hTex"), 1);
		
		glUniformMatrix4fv(CmodelLoc, 1, GL_FALSE, glm::value_ptr(cube.getWorldMatrix()));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lShader.Use();

		glUniformMatrix4fv(LviewLoc, 1, GL_FALSE, glm::value_ptr(gCamera.GetViewMatrix()));
		glUniformMatrix4fv(LprojLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glUniformMatrix4fv(LmodelLoc, 1, GL_FALSE, glm::value_ptr(lightSource.getWorldMatrix()));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwSwapBuffers(gDisplay.GetWindow());
	}
	
	return 0;
}