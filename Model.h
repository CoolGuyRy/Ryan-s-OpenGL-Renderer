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
	
	- Keep in mind that for some reason indices with negative values should be treated
	  as offsets from the end of the list. (SAVE YOU LATER)

	  - Lazy fix for this is to just import to blender then export. Blender automatically
	    gets rid of negative indices.

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