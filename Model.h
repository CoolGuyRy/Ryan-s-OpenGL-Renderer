#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

/*

	TODO:
	
	- For now, I just want to worry about getting the object data into the C++ program.
	  Afterwards I will mess with how to load it into OpenGL.

	- Load vertices into OpenGL Buffer and send it down pipeline

	- Keep in mind that for some reason indices with negative values should be treated
	  as offsets from the end of the list. (SAVE YOU LATER)

	- I can clean up the Model Class by removing mVertices after establishing the 
	  vertex indices

*/

class Model {
public:
	Model();
	Model(std::string);
	
	void Load(std::string);
	void Build();

	std::vector<glm::vec3>& GetVertices();
	std::vector<glm::vec3>& GetNormals();
	std::vector<glm::vec2>& GetTexCoords();

	GLuint mVertexBuffer, mNormalBuffer, mTexBuffer;
private:
	void Clear();

	std::vector<glm::vec3> mVertices;
	std::vector<glm::vec3> mNormals;
	std::vector<glm::vec2> mTexCoords;
};

#endif