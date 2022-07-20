#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>

/*

	TODO:
	
	- For now, I just want to worry about getting the object data into the C++ program.
	  Afterwards I will mess with how to load it into OpenGL.

	- Load vertices into OpenGL Buffer and send it down pipeline

*/

class Model {
public:
	Model();
	Model(std::string);
	
	void Load(std::string);

private:
	void Clear();

	std::vector<glm::vec3> mVertices;
	std::vector<glm::vec3> mNormals;
	std::vector<glm::vec2> mTexCoords;
};

#endif