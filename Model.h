#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

/*

	Model Class:

	- Not responsible for resource deallocation for Mesh, Texture, and Shader

*/

class Model {
public:
	Model(Camera*, glm::mat4);
	Model(Camera*, glm::mat4, Mesh*, Texture*, Shader*);
	Model(Camera*, glm::mat4, Mesh*, Texture*, Shader*, glm::vec3);
	Model(Camera*, glm::mat4, Mesh*, Texture*, Shader*, glm::vec3, glm::vec3);
	Model(Camera*, glm::mat4, Mesh*, Texture*, Shader*, glm::vec3, glm::vec3, glm::vec3);

	void Draw();
	void Load(Mesh*, Texture*, Shader*);

	void UpdatePosition(glm::vec3 p) { mPosition = p; }
	void UpdateRotation(glm::vec3 r) { mRotation = r; }
	void UpdateScale(glm::vec3 s) { mScale = s; }
private:
	glm::mat4 GetModelMatrix();

	Camera* mCamera;
	glm::mat4 mModelMatrix;
	glm::mat4 mProjMatrix;

	glm::vec3 mPosition;
	glm::vec3 mRotation;
	glm::vec3 mScale;
	
	Mesh* mMesh;
	Texture* mTexture;
	Shader* mShader;
};

#endif