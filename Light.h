#ifndef LIGHT_H
#define LIGHT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

enum LightType {
	DEFAULT,
	DIRECTION,
	POINT,
	SPOTLIGHT
};

class Light {
public:
	Light();
	Light(glm::vec3);
	Light(glm::vec3, glm::vec3, glm::vec3);

	void SetAmbient(glm::vec3 a) { mAmbient = a; }
	void SetDiffuse(glm::vec3 d) { mDiffuse = d; }
	void SetSpecular(glm::vec3 s) { mSpecular = s; }
	
	glm::vec3 GetAmbient() { return mAmbient; }
	glm::vec3 GetDiffuse() { return mDiffuse; }
	glm::vec3 GetSpecular() { return mSpecular; }

	virtual LightType GetType() { return DEFAULT; }
protected:
	glm::vec3 mAmbient;
	glm::vec3 mDiffuse;
	glm::vec3 mSpecular;
};

class DirectionalLight : public Light {
public:
	DirectionalLight();
	DirectionalLight(glm::vec3);
	DirectionalLight(glm::vec3, glm::vec3);
	DirectionalLight(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
	
	void SetDirection(glm::vec3 d) { mDirection = d; }

	glm::vec3 GetDirection() { return mDirection; }

	LightType GetType() { return DIRECTION; }
protected:
	glm::vec3 mDirection;
};

class PointLight : public Light {
public:

private:

};
#endif