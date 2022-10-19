#include "Shader.h"

Shader::Shader() {
	mProgram = 0;
}

Shader::Shader(std::string vs, std::string fs) {
	mProgram = 0;
	Add(vs, GL_VERTEX_SHADER);
	Add(fs, GL_FRAGMENT_SHADER);
	Build();
}

Shader::~Shader() {
	for (GLuint shader : mShaders)
		glDeleteShader(shader);
	
	mShaders.clear();
	
	if (glIsProgram(mProgram))
		glDeleteProgram(mProgram);
}

void Shader::Add(std::string src, GLenum type) {
	std::ifstream file(src);
	std::string srcCode;

	if (!file.is_open()) {
		std::cout << "Error: Failed to open file: " << src << std::endl;
		return;
	}

	while (file.good()) {
		std::string line;
		std::getline(file, line);
		srcCode += line + "\n";
	}

	file.close();

	const GLchar* code = srcCode.c_str();

	GLuint tempShader = glCreateShader(type);
	glShaderSource(tempShader, 1, &code, NULL);
	glCompileShader(tempShader);

	GLint result;
	glGetShaderiv(tempShader, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		GLint logLength;
		glGetShaderiv(tempShader, GL_INFO_LOG_LENGTH, &logLength);
		char* log = new char[logLength];
		glGetShaderInfoLog(tempShader, logLength, NULL, log);
		std::cout << "Error: Failed to compile shader: " << log << std::endl;
		delete[] log;
		return;
	}

	mShaders.push_back(tempShader);
}

void Shader::Build() {
	mProgram = glCreateProgram();
	
	for (GLuint shader : mShaders)
		glAttachShader(mProgram, shader);

	glLinkProgram(mProgram);

	GLint result;
	glGetProgramiv(mProgram, GL_LINK_STATUS, &result);
	if (result != GL_TRUE) {
		GLint logLength;
		glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &logLength);
		char* log = new char[logLength];
		glGetProgramInfoLog(mProgram, logLength, NULL, log);
		std::cout << "Error: Failed to link program: " << log << std::endl;
		delete[] log;
		return;
	}

	glUseProgram(0);

	for (GLuint shader : mShaders)
		glDeleteShader(shader);

	mShaders.clear();
}