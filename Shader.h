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
	Shader(std::string, std::string);
	~Shader();

	void Add(std::string, GLenum);
	void Build();
	void Use() { glUseProgram(mProgram); }

	GLuint GetProgram() { return mProgram; }
private:
	GLuint mProgram;
	std::vector<GLuint> mShaders;
};

#endif