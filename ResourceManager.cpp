#include "ResourceManager.h"

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {
	for (auto& shader : mShaders)
		delete shader.second;
	for (auto& texture : mTextures)
		delete texture.second;
	for (auto& mesh : mModels)
		delete mesh.second;
}

void ResourceManager::AddShader(std::string name, Shader* shader) {
	if (mShaders.find(name) != mShaders.end()) {
		std::cout << "Shader already exists: " << name << std::endl;
		return;
	}
	else {
		mShaders[name] = shader;
	}
}
void ResourceManager::AddTexture(std::string name, Texture* texture) {
	if (mTextures.find(name) != mTextures.end()) {
		std::cout << "Texture already exists: " << name << std::endl;
		return;
	}
	else {
		mTextures[name] = texture;
	}
}
void ResourceManager::AddModel(std::string name, Model* model) {
	if (mModels.find(name) != mModels.end()) {
		std::cout << "Mesh already exists: " << name << std::endl;
		return;
	}
	else {
		mModels[name] = model;
	}
}

void ResourceManager::RemoveShader(std::string name) {
	if (mShaders.find(name) != mShaders.end()) {
		delete mShaders[name];
		mShaders.erase(name);
	}
	else {
		std::cout << "Shader does not exist: " << name << std::endl;
	}
}
void ResourceManager::RemoveTexture(std::string name) {
	if (mTextures.find(name) != mTextures.end()) {
		delete mTextures[name];
		mTextures.erase(name);
	}
	else {
		std::cout << "Texture does not exist: " << name << std::endl;
	}
}
void ResourceManager::RemoveModel(std::string name) {
	if (mModels.find(name) != mModels.end()) {
		delete mModels[name];
		mModels.erase(name);
	}
	else {
		std::cout << "Mesh does not exist: " << name << std::endl;
	}
}

Shader* ResourceManager::GetShader(std::string name) {
	if (mShaders.find(name) != mShaders.end()) {
		return mShaders[name];
	}
	else {
		std::cout << "Shader does not exist: " << name << std::endl;
		return nullptr;
	}
}
Texture* ResourceManager::GetTexture(std::string name) {
	if (mTextures.find(name) != mTextures.end()) {
		return mTextures[name];
	}
	else {
		std::cout << "Texture does not exist: " << name << std::endl;
		return nullptr;
	}
}
Model* ResourceManager::GetModel(std::string name) {
	if (mModels.find(name) != mModels.end()) {
		return mModels[name];
	}
	else {
		std::cout << "Mesh does not exist: " << name << std::endl;
		return nullptr;
	}
}