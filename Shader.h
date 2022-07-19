#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/*

	TODO: 

	
*/

class Shader {
public:
	Shader();
	~Shader();

	void AddShader(std::string, GLenum);
	void Build();

	GLuint GetProgram();

private:
	GLuint mProgram;
	std::vector<GLuint> mShaders;
};

#endif