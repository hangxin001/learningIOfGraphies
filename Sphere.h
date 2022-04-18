#pragma once
#ifndef TESTOPENGL__SPHERE
#define TESTOPENGL__SPHERE
#include<cmath>
#include<vector>
#include<glm\glm.hpp>
class Sphere {
public:
	Sphere(const int& prec);	//prec为精度
	inline int GetNumVertices() { return m_numVertics; }
	inline int GetNumIndices() { return m_numIndices; }
	inline std::vector<int>& GetIndices() { return m_indices; }
	inline std::vector<glm::vec3>& GetVertices() { return m_vertices; }
	inline std::vector<glm::vec2>& GetTexCoords() { return m_texCoords; }
	inline std::vector<glm::vec3>& GetNormals() { return m_normales; }
private:
	void init(const int& prec);
	float ToRadians(const float& degress);
private:
	int m_numVertics;
	int m_numIndices;

	std::vector<int> m_indices;				//索引
	std::vector<glm::vec3> m_vertices;		//顶点
	std::vector<glm::vec2> m_texCoords;		//纹理
	std::vector<glm::vec3> m_normales;		//法线
};

#endif