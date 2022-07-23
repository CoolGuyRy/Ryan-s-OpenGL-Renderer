#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Libraries/stb/stb_image.h"

/*

	Model Class Description:
		- I just want a container for related meshes and textures.
		  I will probably expand upon this later. I just wanted to
		  get some practice in with making structures around this API.
		- As of now, the Model Class will only support 1 texture.
		- I have to manually change textures when drawing. This will
		  have to be handled in the Draw() function for this class.
		
		- A potential optimization I could do is send indices to OpenGL
		  instead of the vertices. Because I have the vertices available
		  to me already I just convert beforehand. Maybe if I force OpenGL
		  to do it instead it would run faster.

*/

class Model {
public:
	Model();
	Model(std::string);
	Model(std::string, std::string);

	void Load(std::string, std::string);

	void Draw();
private:
	void LoadMesh(std::string);
	void LoadTexture(std::string);
	void Build();
	void Clear();
	
	GLuint mVAO, mVertexBuffer, mNormalBuffer, mTexBuffer;
	
	GLuint mTexture;
	unsigned char* mTextureData;
	int mTextureWidth, mTextureHeight, mTextureChannels;

	std::vector<glm::vec3> mVertices;
	std::vector<glm::vec3> mNormals;
	std::vector<glm::vec2> mTexCoords;
};
#endif