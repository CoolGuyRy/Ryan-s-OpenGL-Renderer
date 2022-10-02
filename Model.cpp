#include "Model.h"

Model::Model() {
	Clear();
}

Model::Model(std::string objFile) {
	LoadMesh(objFile);
}

Model::Model(std::string objFile, std::string texFile) {
	LoadMesh(objFile);
	LoadTexture(texFile);
	Build();
}

void Model::Load(std::string objFile, std::string texFile) {
	LoadMesh(objFile);
	LoadTexture(texFile);
	Build();
}

void Model::LoadMesh(std::string objFile) {
	Clear();
	std::ifstream file(objFile);

	if (!file.is_open()) {
		std::cout << "Error opening file: " << objFile << std::endl;
		return;
	}

	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec3> tempNormals;
	std::vector<glm::vec2> tempTexCoords;

	while (file.good()) {
		std::string line;
		std::getline(file, line);

		if (line.substr(0, 2) == "v ") {
			glm::vec3 tempVec{};
			int matches = sscanf_s(line.c_str(), "v %f %f %f\n", &tempVec.x, &tempVec.y, &tempVec.z);
			tempVertices.push_back(tempVec);
			continue;
		}
		if (line.substr(0, 2) == "vt") {
			glm::vec2 tempVec{};
			int matches = sscanf_s(line.c_str(), "vt %f %f\n", &tempVec.x, &tempVec.y);
			tempTexCoords.push_back(tempVec);
			continue;
		}
		if (line.substr(0, 2) == "vn") {
			glm::vec3 tempVec{};
			int matches = sscanf_s(line.c_str(), "vn %f %f %f\n", &tempVec.x, &tempVec.y, &tempVec.z);
			tempNormals.push_back(tempVec);
			continue;
		}
		if (line.substr(0, 2) == "f ") {
			int matches = -1;

			size_t v1 = 0, v2 = 0, v3 = 0;
			size_t vt1 = 0, vt2 = 0, vt3 = 0;
			size_t vn1 = 0, vn2 = 0, vn3 = 0;

			matches = sscanf_s(line.c_str(), "f %zd/%zd/%zd %zd/%zd/%zd %zd/%zd/%zd\n", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
			if (matches == 9) { // Format is: f %zd/%zd/%zd %zd/%zd/%zd %zd/%zd/%zd
				mVertices.push_back(tempVertices.at(v1 - 1));
				mVertices.push_back(tempVertices.at(v2 - 1));
				mVertices.push_back(tempVertices.at(v3 - 1));

				mTexCoords.push_back(tempTexCoords.at(vt1 - 1));
				mTexCoords.push_back(tempTexCoords.at(vt2 - 1));
				mTexCoords.push_back(tempTexCoords.at(vt3 - 1));

				mNormals.push_back(tempNormals.at(vn1 - 1));
				mNormals.push_back(tempNormals.at(vn2 - 1));
				mNormals.push_back(tempNormals.at(vn3 - 1));
			}

			matches = sscanf_s(line.c_str(), "f %zd//%zd %zd//%zd %zd//%zd\n", &v1, &vn1, &v2, &vn2, &v3, &vn3);
			if (matches == 6) { // Format is: f %zd//%zd %zd//%zd %zd//%zd
				mVertices.push_back(tempVertices.at(v1 - 1));
				mVertices.push_back(tempVertices.at(v2 - 1));
				mVertices.push_back(tempVertices.at(v3 - 1));

				mNormals.push_back(tempNormals.at(vn1 - 1));
				mNormals.push_back(tempNormals.at(vn2 - 1));
				mNormals.push_back(tempNormals.at(vn3 - 1));
			}

			matches = sscanf_s(line.c_str(), "f %zd/%zd %zd/%zd %zd/%zd\n", &v1, &vt1, &v2, &vt2, &v3, &vt3);
			if (matches == 6) { // Format is: f %zd/%zd %zd/%zd %zd/%zd
				mVertices.push_back(tempVertices.at(v1 - 1));
				mVertices.push_back(tempVertices.at(v2 - 1));
				mVertices.push_back(tempVertices.at(v3 - 1));

				mTexCoords.push_back(tempTexCoords.at(vt1 - 1));
				mTexCoords.push_back(tempTexCoords.at(vt2 - 1));
				mTexCoords.push_back(tempTexCoords.at(vt3 - 1));
			}

			matches = sscanf_s(line.c_str(), "f %zd %zd %zd\n", &v1, &v2, &v3);
			if (matches == 3) { // Format is: f %zd %zd %zd
				mVertices.push_back(tempVertices.at(v1 - 1));
				mVertices.push_back(tempVertices.at(v2 - 1));
				mVertices.push_back(tempVertices.at(v3 - 1));
			}

			continue;
		}
	}

	std::cout << "Finished loading mesh: " << objFile << std::endl;
	std::cout << "Vertices: " << tempVertices.size() << std::endl;
	std::cout << "Texture Coords: " << tempTexCoords.size() << std::endl;
	std::cout << "Normals: " << tempNormals.size() << std::endl;
	std::cout << "Vertex Indices: " << mVertices.size() << std::endl;
	std::cout << "Texture Indices: " << mTexCoords.size() << std::endl;
	std::cout << "Normal Indices: " << mNormals.size() << std::endl;
	std::cout << "Triangles: " << mVertices.size() / 3 << std::endl;
}

void Model::LoadTexture(std::string texFile) {
	mTextureData = stbi_load(texFile.c_str(), &mTextureWidth, &mTextureHeight, &mTextureChannels, 3);

	if (glIsTexture(mTexture)) {
		glDeleteTextures(1, &mTexture);
	}
	
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, mTextureWidth, mTextureHeight);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mTextureWidth, mTextureHeight, GL_RGB, GL_UNSIGNED_BYTE, mTextureData);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(mTextureData);
}

void Model::Draw() {
	// glUseProgram() should be getting called here...

	glBindVertexArray(mVAO);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	// Uniforms should be modified here
	
	glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Model::Build() {
	if (mVertices.size() == 0) {
		std::cout << "Error building model: No vertices to build model from." << std::endl;
		return;
	}

	if (glIsBuffer(mVertexBuffer)) {
		glDeleteBuffers(1, &mVertexBuffer);
	}
	if (glIsBuffer(mTexBuffer)) {
		glDeleteBuffers(1, &mTexBuffer);
	}
	if (glIsVertexArray(mVAO)) {
		glDeleteVertexArrays(1, &mVAO);
	}

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	if (mVertices.size() != 0) {
		glGenBuffers(1, &mVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(glm::vec3), &mVertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
	}

	if (mTexCoords.size() != 0) {
		glGenBuffers(1, &mTexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mTexBuffer);
		glBufferData(GL_ARRAY_BUFFER, mTexCoords.size() * sizeof(glm::vec2), &mTexCoords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
	}

	glBindVertexArray(0);
}

void Model::Clear() {
	mVertices.clear();
	mNormals.clear();
	mTexCoords.clear();
}