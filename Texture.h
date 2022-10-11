#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

#include "Libraries/stb/stb_image.h"
#include "glad/glad.h"

class Texture {
public:
	Texture(std::string);
	~Texture();

	GLuint GetTexture() { return mTexture; }
private:
	GLuint mTexture;
};
#endif