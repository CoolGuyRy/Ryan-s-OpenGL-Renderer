#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

#include "Shader.h"

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

	gShader.AddShader("chapter03s02.vert", GL_VERTEX_SHADER);
	gShader.AddShader("chapter03s03.frag", GL_FRAGMENT_SHADER);
	
	gShader.Build();

	glUseProgram(gShader.GetProgram());

	GLuint vertex_array_object;

	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	double gTime = 0.0;

	glPointSize(5.0f);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// Having some fun here
		GLfloat displace[] = { std::sin(gTime * 0.5) * 0.75f, std::cos(gTime * 0.5) * 0.75f, 0.0f, 0.0f };
		GLfloat color[] = { abs(std::sin(gTime * 0.5)) * 0.5f + 0.5f, abs(std::cos(gTime * 0.5)) * 0.5f + 0.5f, 0.0f, 1.0f };

		// glUniform4fv(0, 1, color);
		glVertexAttrib4fv(0, displace);

		// glDrawArrays(GL_PATCHES, 0, 3); // use when tesselating
		glDrawArrays(GL_TRIANGLES, 0, 3); // use otherwise
		// glDrawArrays(GL_POINTS, 0, 1); for shader chapter02s01.vert

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