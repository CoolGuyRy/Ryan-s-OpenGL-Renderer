#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Model.h"
#include "Light.h"

const unsigned MAX_LIGHTS = 5;

class Scene {
public:
	Scene();

	void AddModel(Model*);
	void AddDirectionalLight(Light*);
	void AddPointLight(Light*);

	void Draw();
private:
	std::vector<Model*> mModels;
	std::vector<Light*> mDirectionalLights;
};
#endif