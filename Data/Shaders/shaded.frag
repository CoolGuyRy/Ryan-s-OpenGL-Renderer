#version 430 core

in vec2 fTex;
in vec3 fNorm;
in vec3 fPos;

out vec4 outColor;

uniform sampler2D tex;

uniform vec3 lightColor = vec3(0.6, 0.9, 0.9);
uniform vec3 lightPos = vec3(1.2, 1.0, 2.0);

void main(void) {
	vec3 ambient = lightColor * 0.1;

	vec3 norm = normalize(fNorm);
	vec3 lightDir = normalize(lightPos - fPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = lightColor * diff;
	
	outColor = texture(tex, fTex) * vec4(ambient + diffuse, 1.0);
}