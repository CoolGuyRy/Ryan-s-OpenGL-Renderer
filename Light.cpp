#include "Light.h"

Light::Light() {
	SetAmbient(glm::vec3(1.0f));
	SetDiffuse(glm::vec3(1.0f));
	SetSpecular(glm::vec3(1.0f));
}
Light::Light(glm::vec3 c) {
	SetAmbient(c);
	SetDiffuse(c);
	SetSpecular(c);
}
Light::Light(glm::vec3 a, glm::vec3 d, glm::vec3 s) {
	SetAmbient(a);
	SetDiffuse(d);
	SetSpecular(s);
}

DirectionalLight::DirectionalLight() {
	SetDirection(glm::vec3(0.0));
	SetAmbient(glm::vec3(1.0f));
	SetDiffuse(glm::vec3(1.0f));
	SetSpecular(glm::vec3(1.0f));
}
DirectionalLight::DirectionalLight(glm::vec3 dir) {
	SetDirection(dir);
	SetAmbient(glm::vec3(1.0f));
	SetDiffuse(glm::vec3(1.0f));
	SetSpecular(glm::vec3(1.0f));
}
DirectionalLight::DirectionalLight(glm::vec3 dir, glm::vec3 c) {
	SetDirection(dir);
	SetAmbient(c);
	SetDiffuse(c);
	SetSpecular(c);
}
DirectionalLight::DirectionalLight(glm::vec3 dir, glm::vec3 a, glm::vec3 d, glm::vec3 s) {
	SetDirection(dir);
	SetAmbient(a);
	SetDiffuse(d);
	SetSpecular(s);
}