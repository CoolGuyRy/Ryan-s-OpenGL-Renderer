#include "Shader.h"

Shader::Shader() {
	mProgram = 0;
}

Shader::~Shader() {
	for (unsigned i = 0; i < mShaders.size(); i++) {
		glDeleteShader(mShaders[i]);
	}
	mShaders.clear();
	
	glDeleteProgram(mProgram);
}

void Shader::AddShader(std::string src, GLenum type) {
	GLuint shader = glCreateShader(type);
	std::ifstream file(src);
	std::string srcCode;

	if (!file.is_open()) {
		std::cout << "Error opening file: " << src << std::endl;
		return;
	}
	
	while (file.good()) {
		std::string line;
		std::getline(file, line);
		srcCode += line + "\n";
	}

	const GLchar* code = srcCode.c_str();

	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	mShaders.push_back(shader);
}

void Shader::Build() {
	mProgram = glCreateProgram();

	for (unsigned i = 0; i < mShaders.size(); i++) {
		glAttachShader(mProgram, mShaders[i]);
	}

	glLinkProgram(mProgram);
	
	for (unsigned i = 0; i < mShaders.size(); i++) {
		glDeleteShader(mShaders[i]);
	}
	mShaders.clear();
}

GLuint Shader::GetProgram() {
	return mProgram;
}