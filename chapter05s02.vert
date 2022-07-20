#version 430 core

layout (location = 0) in vec3 aPos;

out vec4 vs_color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void) {
	gl_Position = proj_matrix * mv_matrix * vec4(aPos, 1.0);
	vs_color = vec4(aPos, 1.0) * 2.0;
}