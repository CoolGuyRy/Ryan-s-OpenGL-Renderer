#include "Model.h"

Model::Model(Camera* c, glm::mat4 p) : mMesh(nullptr), mTexture(nullptr), mShader(nullptr), mCamera(c), mProjMatrix(p) {
	mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	mRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	mScale = glm::vec3(1.0f, 1.0f, 1.0f);
	mModelMatrix = GetModelMatrix();
}

Model::Model(Camera* c, glm::mat4 p, Mesh* m, Texture* t, Shader* s) : mCamera(c), mProjMatrix(p), mMesh(m), mTexture(t), mShader(s) {
	mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	mRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	mScale = glm::vec3(1.0f, 1.0f, 1.0f);
	mModelMatrix = GetModelMatrix();
}

Model::Model(Camera* c, glm::mat4 p, Mesh* m, Texture* t, Shader* s, glm::vec3 pos) : mCamera(c), mProjMatrix(p), mMesh(m), mTexture(t), mShader(s), mPosition(pos) {
	mRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	mScale = glm::vec3(1.0f, 1.0f, 1.0f);
	mModelMatrix = GetModelMatrix();
}

Model::Model(Camera* c, glm::mat4 p, Mesh* m, Texture* t, Shader* s, glm::vec3 pos, glm::vec3 rot) : mCamera(c), mProjMatrix(p), mMesh(m), mTexture(t), mShader(s), mPosition(pos), mRotation(rot) {
	mScale = glm::vec3(1.0f, 1.0f, 1.0f);
	mModelMatrix = GetModelMatrix();
}

Model::Model(Camera* c, glm::mat4 p, Mesh* m, Texture* t, Shader* s, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) : mCamera(c), mProjMatrix(p), mMesh(m), mTexture(t), mShader(s), mPosition(pos), mRotation(rot), mScale(scale) {
	mModelMatrix = GetModelMatrix();
}

void Model::Draw() {
	glBindVertexArray(mMesh->GetVAO());
	glBindBuffer(GL_ARRAY_BUFFER, mMesh->GetVBO());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture->GetTexture());

	GLuint modelLoc = glGetUniformLocation(mShader->GetProgram(), "model");
	GLuint viewLoc = glGetUniformLocation(mShader->GetProgram(), "view");
	GLuint projLoc = glGetUniformLocation(mShader->GetProgram(), "proj");

	mShader->Use();

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(GetModelMatrix()));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mCamera->GetViewMatrix()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mProjMatrix));

	glDrawArrays(GL_TRIANGLES, 0, mMesh->GetVertexCount());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Model::Load(Mesh* m, Texture* t, Shader* s) {
	mMesh = m;
	mTexture = t;
	mShader = s;
}

glm::mat4 Model::GetModelMatrix() {
	glm::mat4 result(1.0f);

	result = glm::translate(result, mPosition);
	result = glm::rotate(result, mRotation.x, glm::vec3(1.0, 0.0, 0.0));
	result = glm::rotate(result, mRotation.y, glm::vec3(0.0, 1.0, 0.0));
	result = glm::rotate(result, mRotation.z, glm::vec3(0.0, 0.0, 1.0));
	result = glm::scale(result, mScale);

	return result;
}
