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

/*
	
	This class will be a singleton that will hold all the 3D resources
	for a game

*/

class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();

	void AddShader(std::string, std::string);
	void AddTexture(std::string, std::string);
	void AddMesh(std::string, std::string);

	void RemoveShader(std::string);
	void RemoveTexture(std::string);
	void RemoveMesh(std::string);
	
	Shader* GetShader(std::string);
	Texture* GetTexture(std::string);
	Mesh* GetMesh(std::string);
private:
	std::map<std::string, Shader*> mShaders;
	std::map<std::string, Mesh*> mMeshes;
	std::map<std::string, Texture*> mTextures;
};

#endif