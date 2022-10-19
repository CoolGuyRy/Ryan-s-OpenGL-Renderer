#version 430 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 fNormal;
in vec3 fTex;

uniform Material material;

out vec4 color;

void main(void) {
	color = vec4(material.diffuse, 1.0);
}