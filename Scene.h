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

	void AddModel(Model);

	void Draw();
private:
	std::vector<Model> mModels;
	std::vector<Light> mLights;
};
#endif