#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Model.h"
#include "Light.h"

class Scene {
public:
	Scene();

	void AddModel(Model*);
	void AddLight(Light*);

	void Draw();
private:
	std::vector<std::pair<std::string, Model*>> mModels;
	std::vector<std::pair<std::string, Light*>> mLights;
};
#endif