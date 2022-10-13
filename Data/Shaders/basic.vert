#version 430 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTex;
layout (location = 2) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 fTex;
out vec3 fNormal;

void main(void) {
	gl_Position = proj * view * model * vec4(vPos, 1.0);
	fTex = vTex;
	fNormal = vNormal;
}