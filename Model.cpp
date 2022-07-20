#include "Model.h"

Model::Model() {
	Clear();
}

Model::Model(std::string objFile) {
	Load(objFile);
}

void Model::Load(std::string objFile) {
	Clear();
	std::ifstream file(objFile);

	if (!file.is_open()) {
		std::cout << "Could not open file: " << objFile << std::endl;
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

	std::cout << "Finished loading object: " << objFile << std::endl;
	std::cout << "Vertices: " << tempVertices.size() << std::endl;
	std::cout << "Texture Coords: " << tempTexCoords.size() << std::endl;
	std::cout << "Normals: " << tempNormals.size() << std::endl;
	std::cout << "Vertex Indices: " << mVertices.size() << std::endl;
	std::cout << "Texture Indices: " << mTexCoords.size() << std::endl;
	std::cout << "Normal Indices: " << mNormals.size() << std::endl;
	std::cout << "Triangles: " << mVertices.size() / 3 << std::endl;
}

void Model::Build() {
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(glm::vec3), &mVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
}

std::vector<glm::vec3>& Model::GetVertices() {
	return mVertices;
}

std::vector<glm::vec3>& Model::GetNormals() {
	return mNormals;
}

std::vector<glm::vec2>& Model::GetTexCoords() {
	return mTexCoords;
}

void Model::Clear() {
	mVertices.clear();
	mNormals.clear();
	mTexCoords.clear();
}