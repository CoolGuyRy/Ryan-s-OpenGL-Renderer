#include "Scene.h"

Scene::Scene() { }

void Scene::AddModel(Model* m) {
	mModels.push_back(m);
}

void Scene::AddDirectionalLight(Light* l) {
	mDirectionalLights.push_back(l);
}

void Scene::AddPointLight(Light* l) {
	
}