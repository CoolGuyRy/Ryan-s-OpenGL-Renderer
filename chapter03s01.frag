#version 430 core

uniform vec4 in_color;

out vec4 color;

void main(void) {
	// Triangle is tesselating, but the color isn't being passed through the stages...
	// color = vec4(1.0, 0.0, 0.0, 1.0); // works
	color = in_color; // works now that i replaced with uniform
}