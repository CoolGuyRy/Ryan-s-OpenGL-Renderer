#version 430 core

in vec2 fTex;

out vec4 color;

uniform sampler2D mTex;
uniform sampler2D hTex;

void main(void) {
	color = mix(texture(mTex, fTex), texture(hTex, fTex), 0.2);
}