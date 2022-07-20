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

	while (file.good()) {
		std::string line;
		std::getline(file, line);

		if (line.substr(0, 2) == "v ") {
			glm::vec3 tempVec{};
			int matches = sscanf_s(line.c_str(), "v %f %f %f\n", &tempVec.x, &tempVec.y, &tempVec.z);
			mVertices.push_back(tempVec);
			continue;
		}
		if (line.substr(0, 2) == "vt") {
			glm::vec2 tempVec{};
			int matches = sscanf_s(line.c_str(), "vt %f %f\n", &tempVec.x, &tempVec.y);
			mTexCoords.push_back(tempVec);
			continue;
		}
		if (line.substr(0, 2) == "vn") {
			glm::vec3 tempVec{};
			int matches = sscanf_s(line.c_str(), "vn %f %f %f\n", &tempVec.x, &tempVec.y, &tempVec.z);
			mNormals.push_back(tempVec);
			continue;
		}
		if (line.substr(0, 2) == "f ") {
			int matches = -1;

			int v1 = 0, v2 = 0, v3 = 0;
			int vt1 = 0, vt2 = 0, vt3 = 0;
			int vn1 = 0, vn2 = 0, vn3 = 0;

			matches = sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
			if (matches == 9) { // Format is: f %d/%d/%d %d/%d/%d %d/%d/%d
				mVertexIndices.push_back(v1);
				mVertexIndices.push_back(v2);
				mVertexIndices.push_back(v3);

				mTextureIndices.push_back(vt1);
				mTextureIndices.push_back(vt2);
				mTextureIndices.push_back(vt3);

				mNormalIndices.push_back(vn1);
				mNormalIndices.push_back(vn2);
				mNormalIndices.push_back(vn3);
			}

			matches = sscanf_s(line.c_str(), "f %d//%d %d//%d %d//%d\n", &v1, &vn1, &v2, &vn2, &v3, &vn3);
			if (matches == 6) { // Format is: f %d//%d %d//%d %d//%d
				mVertexIndices.push_back(v1);
				mVertexIndices.push_back(v2);
				mVertexIndices.push_back(v3);

				mNormalIndices.push_back(vn1);
				mNormalIndices.push_back(vn2);
				mNormalIndices.push_back(vn3);
			}

			matches = sscanf_s(line.c_str(), "f %d/%d %d/%d %d/%d\n", &v1, &vt1, &v2, &vt2, &v3, &vt3);
			if (matches == 6) { // Format is: f %d/%d %d/%d %d/%d
				mVertexIndices.push_back(v1);
				mVertexIndices.push_back(v2);
				mVertexIndices.push_back(v3);

				mTextureIndices.push_back(vt1);
				mTextureIndices.push_back(vt2);
				mTextureIndices.push_back(vt3);
			}

			matches = sscanf_s(line.c_str(), "f %d %d %d\n", &v1, &v2, &v3);
			if (matches == 3) { // Format is: f %d %d %d
				mVertexIndices.push_back(v1);
				mVertexIndices.push_back(v2);
				mVertexIndices.push_back(v3);
			}

			continue;
		}
	}

	std::cout << "Finished loading object: " << objFile << std::endl;
	std::cout << "Vertices: " << mVertices.size() << std::endl;
	std::cout << "Texture Coords: " << mTexCoords.size() << std::endl;
	std::cout << "Normals: " << mNormals.size() << std::endl;
	std::cout << "Vertex Indices: " << mVertexIndices.size() << std::endl;
	std::cout << "Texture Indices: " << mTextureIndices.size() << std::endl;
	std::cout << "Normal Indices: " << mNormalIndices.size() << std::endl;
	std::cout << "Triangles: " << mVertexIndices.size() / 3 << std::endl;
}

void Model::Clear() {
	mVertices.clear();
	mNormals.clear();
	mTexCoords.clear();
}