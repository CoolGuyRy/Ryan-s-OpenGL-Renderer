#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "Libraries/stb/stb_image.h"

#include "Shader.h"
#include "Model.h"

void KeyCallback(GLFWwindow*, int, int, int, int);

class Renderer {
public:
	Renderer(unsigned, unsigned);
	~Renderer();

	void Init();
	void Run();
private:
	void Input();
	void Update(float);
	void Render();

	std::vector<Model> mModels;

	GLFWwindow* mWindow;
	unsigned mWidth, mHeight;
	double mTime;
};

#endif