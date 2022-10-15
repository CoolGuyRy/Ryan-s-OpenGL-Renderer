#include "Mesh.h"

Mesh::Mesh() : mVAO(0), mVBO(0), mEBO(0), mNBO(0), mTBO(0) {
	
}

Mesh::Mesh(std::string file) : mVAO(0), mVBO(0), mEBO(0), mNBO(0), mTBO(0) {
	LoadMesh(file);
	Build();
}

void Mesh::LoadMesh(std::string src) {
	Clear();
	std::ifstream file(src);

	if (!file.is_open()) {
		std::cout << "Error opening file: " << src << std::endl;
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

	//std::cout << "Finished loading mesh: " << src << std::endl;
	//std::cout << "Vertices: " << tempVertices.size() << std::endl;
	//std::cout << "Texture Coords: " << tempTexCoords.size() << std::endl;
	//std::cout << "Normals: " << tempNormals.size() << std::endl;
	//std::cout << "Vertex Indices: " << mVertices.size() << std::endl;
	//std::cout << "Texture Indices: " << mTexCoords.size() << std::endl;
	//std::cout << "Normal Indices: " << mNormals.size() << std::endl;
	std::cout << "Triangles: " << mVertices.size() / 3 << std::endl;
}

void Mesh::Build() {
	if (mVertices.size() == 0) {
		std::cout << "Error building model: No vertices to build model from." << std::endl;
		return;
	}

	if (glIsBuffer(mVBO))
		glDeleteBuffers(1, &mVBO);
	if (glIsBuffer(mEBO))
		glDeleteBuffers(1, &mEBO);
	if (glIsBuffer(mNBO))
		glDeleteBuffers(1, &mNBO);
	if (glIsBuffer(mTBO))
		glDeleteBuffers(1, &mTBO);
	if (glIsVertexArray(mVAO))
		glDeleteVertexArrays(1, &mVAO);

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	if (mVertices.size() != 0) {
		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(glm::vec3), &mVertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
	}

	if (mTexCoords.size() != 0) {
		glGenBuffers(1, &mTBO);
		glBindBuffer(GL_ARRAY_BUFFER, mTBO);
		glBufferData(GL_ARRAY_BUFFER, mTexCoords.size() * sizeof(glm::vec2), &mTexCoords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
	}

	if (mNormals.size() != 0) {
		glGenBuffers(1, &mNBO);
		glBindBuffer(GL_ARRAY_BUFFER, mNBO);
		glBufferData(GL_ARRAY_BUFFER, mNormals.size() * sizeof(glm::vec3), &mNormals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(2);
	}

	glBindVertexArray(0);
}

void Mesh::Clear() {
	mVertices.clear();
	mIndices.clear();
	mNormals.clear();
	mTexCoords.clear();
}