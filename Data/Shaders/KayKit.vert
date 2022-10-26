#version 430 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vTex;

out vec3 fPos;
out vec3 fNormal;
out vec3 fTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(void) {
	fPos = vec3(model * vec4(vPos, 1.0));
	fNormal = vec3(model * vec4(vNormal, 0.0)); // change later for non-uniform scaling
	fTex = vTex;

	gl_Position = proj * view * model * vec4(vPos, 1.0);
}