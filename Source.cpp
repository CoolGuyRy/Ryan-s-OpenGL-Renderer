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

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

    gShader.AddShader("chapter02s02.vert", GL_VERTEX_SHADER);
    gShader.AddShader("chapter02s01.frag", GL_FRAGMENT_SHADER);
    gShader.Build();

    glUseProgram(gShader.GetProgram());

    GLuint vertex_array_object;

    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    double gTime = 0.0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glPointSize(40.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);
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