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

DirectionalLight::DirectionalLight() : Light() {
	SetDirection(glm::vec3(0.0));
}
DirectionalLight::DirectionalLight(glm::vec3 dir) : Light() {
	SetDirection(dir);
}
DirectionalLight::DirectionalLight(glm::vec3 dir, glm::vec3 c) : Light(c) {
	SetDirection(dir);
}
DirectionalLight::DirectionalLight(glm::vec3 dir, glm::vec3 a, glm::vec3 d, glm::vec3 s) : Light(a, d, s) {
	SetDirection(dir);
}

PointLight::PointLight() : Light() {
	SetPosition(glm::vec3(0.0));

	mConstant = 1.0f;
	mLinear = 0.09f;
	mQuadratic = 0.032f;
}
PointLight::PointLight(glm::vec3 p) : Light() {
	SetPosition(p);

	mConstant = 1.0f;
	mLinear = 0.09f;
	mQuadratic = 0.032f;
}
PointLight::PointLight(glm::vec3 p, glm::vec3 c) : Light(c) {
	SetPosition(p);

	mConstant = 1.0f;
	mLinear = 0.09f;
	mQuadratic = 0.032f;
}
PointLight::PointLight(glm::vec3 p, glm::vec3 c, glm::vec3 f) : Light(c) {
	SetPosition(p);

	mConstant = f.x;
	mLinear = f.y;
	mQuadratic = f.z;
}
PointLight::PointLight(glm::vec3 p, glm::vec3 a, glm::vec3 d, glm::vec3 s) : Light(a, d, s) {
	SetPosition(p);
	
	mConstant = 1.0f;
	mLinear = 0.09f;
	mQuadratic = 0.032f;
}
PointLight::PointLight(glm::vec3 p, glm::vec3 a, glm::vec3 d, glm::vec3 s, glm::vec3 f) : Light(a, d, s) {
	SetPosition(p);

	mConstant = f.x;
	mLinear = f.y;
	mQuadratic = f.z;
}