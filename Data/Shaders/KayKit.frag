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
struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 fPos;
in vec3 fNormal;
in vec3 fTex;

uniform Material material;
uniform uint numDLights;
uniform DirectionalLight dLight[5];

vec4 calcDirectionLight(unsigned int index) {
	vec3 ambient = material.ambient * dLight[index].ambient;

	vec3 norm = normalize(fNormal);
	vec3 lightDir = normalize(dLight[index].direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = material.diffuse * dLight[index].diffuse * diff;

	// todo: calculate specular

	return vec4(ambient + diffuse, 1.0);
}

vec4 calcPointLight() {

	return vec4(1.0);
}

void main(void) {
	for (unsigned int i = 0; i < numDLights; i++) {
		color += calcDirectionLight(i);
	}
}