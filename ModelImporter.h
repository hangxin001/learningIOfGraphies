#pragma once
#ifndef TESTOPENGL__MODELIMPORTER
#define TESTOPENGL__MODELIMPORTER
#include<vector>
#include<glm/glm.hpp>
#include<string>
class ImportedModel {
public:

	ImportedModel(const char* filePath);
	ImportedModel(const std::string& filePath);
	int getNumVertices() { return m_numVertices; }
	std::vector<glm::vec3> getVertices() { return m_vertices; }
	std::vector<glm::vec2> getTextureCoords() { return m_texCoords; }
	std::vector<glm::vec3> getNormals() { return m_normalVecs; }
private:
	int m_numVertices;
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_texCoords;
	std::vector<glm::vec3> m_normalVecs;
};

class ModelImporter {
public:
	ModelImporter(){};
	void parseOBJ(const char* filePath);
	void parseOBJ(const std::string& filePath);
	int getNumVertices() { return m_triangleVerts.size() / 3; }
	std::vector<float> getVertices() { return m_triangleVerts; }
	std::vector<float> getTextureCoordinates() { return m_textureCoords; }
	std::vector<float> getNormals() { return m_normals; }

private:
	// 从OBJ文件读取的数值
	std::vector<float> m_vertVals;
	std::vector<float> m_stVals;
	std::vector<float> m_normVals;

	// 保存为顶点属性以供后续使用的数值
	std::vector<float> m_triangleVerts;
	std::vector<float> m_textureCoords;
	std::vector<float> m_normals;
};

#endif