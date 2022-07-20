#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#include "Shader.h"
#include "Model.h"

/*

	TODO:

	- Make a window class to clean up this main mess.

*/

int main(void) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Specify Window settings / OpenGL versions to use for program */
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 960, "OpenGL Renderer", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Load pointers to OpenGL functions 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	Shader gShader;
	gShader.AddShader("chapter05s02.vert", GL_VERTEX_SHADER);
	gShader.AddShader("chapter05s02.frag", GL_FRAGMENT_SHADER);
	gShader.Build();

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Model gModel("Models/cow.obj");
	gModel.Build();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glm::mat4 proj_matrix = glm::perspective(glm::radians(45.0f), 1280.0f / 960.0f, 0.1f, 100.0f);

	GLuint mv_location = glGetUniformLocation(gShader.GetProgram(), "mv_matrix");
	GLuint proj_location = glGetUniformLocation(gShader.GetProgram(), "proj_matrix");
	
	double gTime = 0.0;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));

		glUseProgram(gShader.GetProgram());

		float f = (float)gTime * (float)glm::pi<float>() * 0.25f;

		glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, -8.0));
		mv_matrix *= glm::rotate(mv_matrix, f, glm::vec3(0.0, 1.0, 0.0));

		glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));
		glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(proj_matrix));

		glDrawArrays(GL_TRIANGLES, 0, gModel.GetVertices().size());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		// Update time value
		gTime = glfwGetTime();
	}

	// Properly exit glfw
	glfwTerminate();

	// Check for errors (only call if crashing immediately)
	// std::cin.get();
	
	return 0;
}