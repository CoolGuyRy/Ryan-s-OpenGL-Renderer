#version 430 core

out vec4 color;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct DirectionalLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 fPos;
in vec3 fNormal;
in vec3 fTex;

uniform Material material;
uniform DirectionalLight dLight;

void main(void) {
	vec3 ambient = material.ambient * dLight.ambient;

	vec3 norm = normalize(fNormal);
	vec3 lightDir = normalize(dLight.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = material.diffuse * dLight.diffuse * diff;

	color = vec4(ambient + diffuse, 1.0);
}