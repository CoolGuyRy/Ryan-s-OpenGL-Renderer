#include "Model.h"

Model::Model() {
	Clear();
}

Model::Model(std::string objFile) {
	Clear();
	Load(objFile);
}

void Model::Load(std::string objFile) {
	// TODO: Implement
}

void Model::Clear() {
	mVertices.clear();
	mNormals.clear();
	mTexCoords.clear();
}