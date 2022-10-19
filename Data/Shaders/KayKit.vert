#version 430 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 fNormal;
out vec3 fTex;

void main(void) {
	gl_Position = proj * view * model * vec4(vPos, 1.0);
	fNormal = vNormal;
	fTex = vTex;
}