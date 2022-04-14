#pragma once
#ifndef __TESTOPENGL__TOURUS__
#define __TESTOPENGL__TOURUS__
#include<cmath>
#include<vector>
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include"Utils.h"
class Torus
{
public:
	Torus() : m_numIndices(0), m_numVertices(0), m_prec(0),m_inner(0),m_outer(0){}
	Torus(const float& innerRadius,const float& outerRadius,const int& prec);
	inline int GetNumVertices() { return m_numVertices; }
	inline int GetNumIndices() { return m_numIndices; }

	inline std::vector<int>& GetIndices() { return m_indices; }
	inline std::vector<glm::vec3>& GetVertices() { return m_vertices; }
	inline std::vector<glm::vec2>& GetTexCoords() { return m_texCoords; }
	inline std::vector<glm::vec3>& GetNormals() {return m_normals; }
	inline std::vector<glm::vec3>& GetStangents() { return m_sTangents; }
	inline std::vector<glm::vec3>& GetTtangents() {return m_tTangents; }
private:
	void init(const float& innerRadius, const float& outerRadius, const int& prec);
private:
	int m_numVertices;
	int m_numIndices;
	int m_prec;
	float m_inner;
	float m_outer;
	std::vector<int> m_indices;
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_texCoords;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec3> m_sTangents;
	std::vector<glm::vec3> m_tTangents;
};


#endif