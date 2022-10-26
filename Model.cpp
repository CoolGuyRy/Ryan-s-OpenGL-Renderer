#include "Model.h"

Model::Model(Camera* cam, glm::mat4 proj, std::string src, Shader* shade) : mCamera(cam), mProjMatrix(proj), mShader(shade) {
	mPosition = glm::vec3(0.0f);
	mRotation = glm::vec3(0.0f);
	mScale = glm::vec3(1.0f);
	mModelMatrix = GetModelMatrix();

	Load(src);
}
Model::Model(Camera* cam, glm::mat4 proj, std::string src, Shader* shade, glm::vec3 pos) : mCamera(cam), mProjMatrix(proj), mShader(shade), mPosition(pos) {
	mRotation = glm::vec3(0.0f);
	mScale = glm::vec3(1.0f);
	mModelMatrix = GetModelMatrix();

	Load(src);
}
Model::Model(Camera* cam, glm::mat4 proj, std::string src, Shader* shade, glm::vec3 pos, glm::vec3 rot) : mCamera(cam), mProjMatrix(proj), mShader(shade), mPosition(pos), mRotation(rot) {
	mScale = glm::vec3(1.0f);
	mModelMatrix = GetModelMatrix();

	Load(src);
}
Model::Model(Camera* cam, glm::mat4 proj, std::string src, Shader* shade, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) : mCamera(cam), mProjMatrix(proj), mShader(shade), mPosition(pos), mRotation(rot), mScale(scale) {
	mModelMatrix = GetModelMatrix();

	Load(src);
}

void Model::Load(std::string src) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(src, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_PreTransformVertices);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Error: " << importer.GetErrorString() << std::endl;
		return;
	}

	for (unsigned i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];
		mMeshes.push_back(new Mesh(mesh, scene));
	}
}
void Model::Draw() {
	for (unsigned i = 0; i < mMeshes.size(); i++) {
		glBindVertexArray(mMeshes.at(i)->GetVAO());
		
		mShader->Use();

		GLuint modelLoc = glGetUniformLocation(mShader->GetProgram(), "model");
		GLuint viewLoc = glGetUniformLocation(mShader->GetProgram(), "view");
		GLuint projLoc = glGetUniformLocation(mShader->GetProgram(), "proj");
		
		GLuint ambientLoc = glGetUniformLocation(mShader->GetProgram(), "material.ambient");
		GLuint diffuseLoc = glGetUniformLocation(mShader->GetProgram(), "material.diffuse");
		GLuint specularLoc = glGetUniformLocation(mShader->GetProgram(), "material.specular");
		GLuint shininessLoc = glGetUniformLocation(mShader->GetProgram(), "material.shininess");

		GLuint dLightDirLoc = glGetUniformLocation(mShader->GetProgram(), "dLight.direction");
		GLuint dLightAmbientLoc = glGetUniformLocation(mShader->GetProgram(), "dLight.ambient");
		GLuint dLightDiffuseLoc = glGetUniformLocation(mShader->GetProgram(), "dLight.diffuse");
		GLuint dLightSpecularLoc = glGetUniformLocation(mShader->GetProgram(), "dLight.specular");


		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(GetModelMatrix()));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mCamera->GetViewMatrix()));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mProjMatrix));

		glUniform3fv(ambientLoc, 1, glm::value_ptr(mMeshes.at(i)->GetMaterial().mAmbient));
		glUniform3fv(diffuseLoc, 1, glm::value_ptr(mMeshes.at(i)->GetMaterial().mDiffuse));
		glUniform3fv(specularLoc, 1, glm::value_ptr(mMeshes.at(i)->GetMaterial().mSpecular));
		glUniform1f(shininessLoc, mMeshes.at(i)->GetMaterial().mShininess);

		glUniform3fv(dLightDirLoc, 1, glm::value_ptr(mCamera->GetCameraPos()));
		glUniform3fv(dLightAmbientLoc, 1, glm::value_ptr(glm::vec3(1.0f)));
		glUniform3fv(dLightDiffuseLoc, 1, glm::value_ptr(glm::vec3(1.0f)));
		glUniform3fv(dLightSpecularLoc, 1, glm::value_ptr(glm::vec3(1.0f)));
		
		glDrawElements(GL_TRIANGLES, mMeshes.at(i)->GetIndices(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
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
