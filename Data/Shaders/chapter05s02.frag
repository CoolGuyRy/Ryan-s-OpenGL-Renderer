#version 430 core

in vec4 vs_color;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D tex;

void main(void) {
	color = texture(tex, TexCoord);
}