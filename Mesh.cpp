#include "Mesh.h"

Mesh::Mesh() : mVAO(0), mVBO(0), mEBO(0), mNBO(0), mTBO(0) {
	mMaterial.mAmbient = mMaterial.mDiffuse = mMaterial.mSpecular = glm::vec3(0.0f);
	mMaterial.mShininess = 0.0f;
	mIndices = 0;
}

Mesh::Mesh(aiMesh* m, const aiScene* s) : mVAO(0), mVBO(0), mEBO(0), mNBO(0), mTBO(0) {
	mIndices = 0;
	Load(m, s);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
	glDeleteBuffers(1, &mEBO);
	glDeleteBuffers(1, &mNBO);
	glDeleteBuffers(1, &mTBO);
}

void Mesh::Load(aiMesh* m, const aiScene* s) {
	std::vector<aiVector3D> vertices, normals, texcoords;
	std::vector<unsigned> indices;

	aiString matName; aiColor3D ambient, diffuse, specular;
	
	s->mMaterials[m->mMaterialIndex]->Get(AI_MATKEY_NAME, mMaterial.mName);
	s->mMaterials[m->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
	s->mMaterials[m->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	s->mMaterials[m->mMaterialIndex]->Get(AI_MATKEY_COLOR_SPECULAR, specular);
	s->mMaterials[m->mMaterialIndex]->Get(AI_MATKEY_SHININESS, mMaterial.mShininess);
	
	mMaterial.mAmbient = glm::vec3(ambient.r, ambient.g, ambient.b);
	mMaterial.mDiffuse = glm::vec3(diffuse.r, diffuse.g, diffuse.b);
	mMaterial.mSpecular = glm::vec3(specular.r, specular.g, specular.b);

	for (unsigned i = 0; i < m->mNumFaces; i++) {
		for (unsigned j = 0; j < m->mFaces[i].mNumIndices; j++) {
			indices.push_back(m->mFaces[i].mIndices[j]);
		}
	}
	mIndices = (unsigned)indices.size();
	
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, m->mNumVertices * sizeof(aiVector3D), m->mVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &mNBO);
	glBindBuffer(GL_ARRAY_BUFFER, mNBO);
	glBufferData(GL_ARRAY_BUFFER, m->mNumVertices * sizeof(aiVector3D), m->mNormals, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &mTBO);
	glBindBuffer(GL_ARRAY_BUFFER, mTBO);
	glBufferData(GL_ARRAY_BUFFER, m->mNumVertices * sizeof(aiVector3D), m->mTextureCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}