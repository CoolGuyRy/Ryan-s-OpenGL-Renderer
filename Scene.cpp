#include "Scene.h"

Scene::Scene() { }

void Scene::AddModel(Model* m) {
	mModels.push_back(std::make_pair(std::to_string(mModels.size()), m));
}

void Scene::AddLight(Light* l) {
	mLights.push_back(std::make_pair(std::to_string(mLights.size()), l));
}