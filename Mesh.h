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

class Mesh {
public:
	Mesh();
	Mesh(std::string);
	~Mesh();

	void Load(std::string);

	unsigned GetIndicesCount() { return (unsigned)mIndices.size(); }

	GLuint GetVAO() { return mVAO; }
	GLuint GetVBO(int i) { return mVBO.at(i); }
	GLuint GetEBO(int i) { return mEBO.at(i); }
	GLuint GetNBO(int i) { return mNBO.at(i); }
	GLuint GetTBO(int i) { return mTBO.at(i); }
private:
	void Cleanup();
	
	GLuint mVAO;
	std::vector<GLuint> mVBO, mEBO, mNBO, mTBO;
	std::vector<aiVector3D> mVertices, mNormals, mTexCoords;
	std::vector<unsigned int> mIndices;
};
#endif