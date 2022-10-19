#version 430 core

in vec3 fNormal;
in vec3 fTex;

out vec4 color;

uniform sampler2D tex;

void main(void) {
	// color = vec4(1.0, 1.0, 1.0, 1.0);
	color = texture(tex, fTex.xy);
}