#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/*

	This Mesh class can only load obj files with vertices, normals, texture coordinates, and is indexed. 

	Something to think on: If you have a standard for how objects are loaded. Do you really need
	a VAO for each Mesh?
	
*/

struct Material {
	glm::vec3 mAmbient;
	glm::vec3 mDiffuse;
	glm::vec3 mSpecular;
	float mShininess;
};

class Mesh {
public:
	Mesh();
	Mesh(aiMesh*, const aiScene*);
	~Mesh();

	void Load(aiMesh*, const aiScene*);
	
	unsigned GetIndices() { return mIndices; }
	Material GetMaterial()  { return mMaterial; }
	GLuint GetVAO() { return mVAO; }
private:
	Material mMaterial;
	GLuint mVAO, mVBO, mEBO, mNBO, mTBO;
	unsigned mIndices;
};
#endif