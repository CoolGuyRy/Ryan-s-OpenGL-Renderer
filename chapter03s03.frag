#version 430 core

in vec4 vs_color;

out vec4 color;

void main(void) {
	color = vs_color;
}

// Simple fragment shader that just outputs the color retrieved from the vertex shader.