#include "Scene.h"

Scene::Scene() { }

void Scene::AddModel(Model model) {
	mModels.push_back(model);
}

void Scene::Draw() {
	for (Model model : mModels)
		model.Draw();
}