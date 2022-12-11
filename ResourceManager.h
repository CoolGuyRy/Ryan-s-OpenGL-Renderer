#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Model.h"

/*
	
	This class will be a singleton that will hold all the 3D resources
	for a game

*/

class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();

	void AddShader(std::string, Shader*);
	void AddTexture(std::string, Texture*);
	void AddModel(std::string, Model*);

	void RemoveShader(std::string);
	void RemoveTexture(std::string);
	void RemoveModel(std::string);
	
	Shader* GetShader(std::string);
	Texture* GetTexture(std::string);
	Model* GetModel(std::string);
private:
	std::map<std::string, Shader*> mShaders;
	std::map<std::string, Texture*> mTextures;
	std::map<std::string, Model*> mModels;
};
#endif