#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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

	void LoadMesh(std::string);
	void Build();

	GLuint GetVAO() { return mVAO; }
	GLuint GetVBO() { return mVBO; }
	GLuint GetEBO() { return mEBO; }
	GLuint GetNBO() { return mNBO; }
	GLuint GetTBO() { return mTBO; }

	GLuint GetVertexCount() { return (unsigned)mVertices.size(); }
private:
	void Clear();
	
	GLuint mVAO, mVBO, mEBO, mNBO, mTBO;

	std::vector<glm::vec3> mVertices;
	std::vector<glm::vec3> mIndices;
	std::vector<glm::vec3> mNormals;
	std::vector<glm::vec2> mTexCoords;
};
#endif