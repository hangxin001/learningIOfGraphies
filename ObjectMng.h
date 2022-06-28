#pragma once
#ifndef TESTOPENGL__OBJECTMNG
#define TESTOPENGL__OBJECTMNG
#include<vector>
#include<glm/ext.hpp>
#include<glm/gtx/string_cast.hpp>
class Object3D
{
	
	virtual int getNumVertices() { return m_numVertices; };
	virtual std::vector<glm::vec3> getVertices() { return m_vertices; };
	virtual std::vector<glm::vec2> getTextureCoords() { return m_texCoords; };
	virtual std::vector<glm::vec3> getNormals() { return m_normalVecs; };
private:
	int m_numVertices;
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_texCoords;
	std::vector<glm::vec3> m_normalVecs;

};

class ObjectMng {

};
#endif