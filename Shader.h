#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Shader {
public:
	Shader();
	Shader(std::string);
	Shader(std::string, std::string);
	~Shader();

	void AddShader(std::string, GLenum);
	void Build();

	GLuint GetProgram();

private:
	GLuint mProgram;
	std::vector<GLuint> mShaders;
};
#endif