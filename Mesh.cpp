#include "Mesh.h"

Mesh::Mesh() : mVAO(0) { }

Mesh::Mesh(std::string fileSrc) {
	Load(fileSrc);
}

Mesh::~Mesh() {
	
}

void Mesh::Load(std::string fileSrc) {
	Assimp::Importer mImporter;
	const aiScene* mScene = mImporter.ReadFile(fileSrc, aiProcess_Triangulate | aiProcess_RemoveRedundantMaterials);

	if (!mScene) {
		std::cout << "Error: " << mImporter.GetErrorString() << std::endl;
		return;
	}

	std::cout << "Mesh loaded: " << fileSrc << std::endl;

	Cleanup();

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	for (unsigned i = 0; i < mScene->mNumMeshes; i++) {
		for (unsigned j = 0; j < mScene->mMeshes[i]->mNumVertices; j++) {
			mVertices.push_back(mScene->mMeshes[i]->mVertices[j]);
			mNormals.push_back(mScene->mMeshes[i]->mNormals[j]);
			mTexCoords.push_back(mScene->mMeshes[i]->mTextureCoords[0][j]);
		}
	}

	for (unsigned i = 0; i < mScene->mMeshes[0]->mNumFaces; i++) {
		for (unsigned j = 0; j < mScene->mMeshes[0]->mFaces[i].mNumIndices; j++) {
			mIndices.push_back(mScene->mMeshes[0]->mFaces[i].mIndices[j]);
		}
	}

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(aiVector3D), &mVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	GLuint nbo;
	glGenBuffers(1, &nbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, mNormals.size() * sizeof(aiVector3D), &mNormals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	GLuint tbo;
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, mTexCoords.size() * sizeof(aiVector3D), &mTexCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::Cleanup() {
	for (GLuint buffer : mVBO) {
		if (glIsBuffer(buffer))
			glDeleteBuffers(1, &buffer);
	}
	for (GLuint buffer : mEBO) {
		if (glIsBuffer(buffer))
			glDeleteBuffers(1, &buffer);
	}
	mEBO.clear();
	for (GLuint buffer : mNBO) {
		if (glIsBuffer(buffer))
			glDeleteBuffers(1, &buffer);
	}
	mNBO.clear();
	for (GLuint buffer : mTBO) {
		if (glIsBuffer(buffer))
			glDeleteBuffers(1, &buffer);
	}
	mTBO.clear();
	glDeleteVertexArrays(1, &mVAO);
}