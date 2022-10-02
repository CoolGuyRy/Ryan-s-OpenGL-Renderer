#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "Shader.h"
#include "Model.h"

/*

	TODO:

	- Make a window class to clean up this main mess.

*/

struct input {
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
	bool SPACE = false;
} gInput;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		gInput.W = true;
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		gInput.A = true;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		gInput.S = true;
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		gInput.D = true;
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		gInput.SPACE = true;
	
	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		gInput.W = false;
	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		gInput.A = false;
	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		gInput.S = false;
	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		gInput.D = false;
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
		gInput.SPACE = false;
}

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

	/* Fix stbi image flip way before loading any images */
	stbi_set_flip_vertically_on_load(true);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	// Load pointers to OpenGL functions 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	Shader gShader;
	gShader.AddShader("Data/Shaders/chapter05s02.vert", GL_VERTEX_SHADER);
	gShader.AddShader("Data/Shaders/chapter05s02.frag", GL_FRAGMENT_SHADER);
	gShader.Build();

	std::vector<std::pair<std::string, std::string>> gModelPaths; unsigned int gModelIter = 0;
	gModelPaths.push_back(std::make_pair("Data/Models/cube.obj", "Data/Textures/container.jpg"));
	gModelPaths.push_back(std::make_pair("Data/Models/cube.obj", "Data/Textures/grass.jpg"));
	gModelPaths.push_back(std::make_pair("Data/Models/bunny.obj", "Data/Textures/bunny.jpg"));
	gModelPaths.push_back(std::make_pair("Data/Models/crab.obj", "Data/Textures/crab.png"));
	gModelPaths.push_back(std::make_pair("Data/Models/drone.obj", "Data/Textures/drone.png"));
	gModelPaths.push_back(std::make_pair("Data/Models/efa.obj", "Data/Textures/efa.png"));
	gModelPaths.push_back(std::make_pair("Data/Models/f22.obj", "Data/Textures/f22.png"));
	gModelPaths.push_back(std::make_pair("Data/Models/f117.obj", "Data/Textures/f117.png"));
	gModelPaths.push_back(std::make_pair("Data/Models/ivan.obj", "Data/Textures/ivan.jpg"));

	
	Model gModel(gModelPaths.at(gModelIter).first, gModelPaths.at(gModelIter).second);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glm::mat4 proj_matrix = glm::perspective(glm::radians(45.0f), 1280.0f / 960.0f, 0.1f, 100.0f);
	glm::mat4 mv_matrix = glm::mat4(1.0);

	GLuint mvp_location = glGetUniformLocation(gShader.GetProgram(), "mvp");

	double gTime = 0.0;

	glm::vec3 cameraPos(0.0, 0.0, -8.0);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Poll for and process events */
		glfwPollEvents();

		/* Render here */
		glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
		glClearBufferfv(GL_DEPTH, 0, glm::value_ptr(glm::vec4(1.0f)));
		
		float f = (float)gTime * (float)glm::pi<float>() * 0.25f;

		if (gInput.W) {
			cameraPos.z -= 0.1f;
		}
		if (gInput.A) {
			cameraPos.x -= 0.1f;
		}
		if (gInput.S) {
			cameraPos.z += 0.1f;
		}
		if (gInput.D) {
			cameraPos.x += 0.1f;
		}
		if (gInput.SPACE) {
			gModelIter = (gModelIter + 1) % gModelPaths.size();
			
			gModel.Load(gModelPaths.at(gModelIter).first, gModelPaths.at(gModelIter).second);
			
			gInput.SPACE = false;
		}

		mv_matrix = glm::scale(glm::mat4(1.0), glm::vec3(1.0, 1.0, 1.0));
		mv_matrix = glm::translate(mv_matrix, cameraPos);
		mv_matrix *= glm::rotate(mv_matrix, f, glm::vec3(0.0, 1.0, 0.0));

		glUseProgram(gShader.GetProgram());

		glm::mat4 mvp = proj_matrix * mv_matrix;

		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

		gModel.Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		// Update time value
		gTime = glfwGetTime();
	}

	// Properly exit glfw
	glfwTerminate();

	// Check for errors (only call if crashing immediately)
	// std::cin.get();
	
	return 0;
}