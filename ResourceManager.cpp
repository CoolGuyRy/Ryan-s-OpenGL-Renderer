#include "ResourceManager.h"

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {
	// Todo: Delete all resources
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
void ResourceManager::AddMesh(std::string name, Mesh* mesh) {
	if (mMeshes.find(name) != mMeshes.end()) {
		std::cout << "Mesh already exists: " << name << std::endl;
		return;
	}
	else {
		mMeshes[name] = mesh;
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
void ResourceManager::RemoveMesh(std::string name) {
	if (mMeshes.find(name) != mMeshes.end()) {
		delete mMeshes[name];
		mMeshes.erase(name);
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
Mesh* ResourceManager::GetMesh(std::string name) {
	if (mMeshes.find(name) != mMeshes.end()) {
		return mMeshes[name];
	}
	else {
		std::cout << "Mesh does not exist: " << name << std::endl;
		return nullptr;
	}
}