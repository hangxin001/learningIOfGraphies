#include"Sphere.h"
#include<numbers>
#include<iostream>
Sphere::Sphere(const int& prec) {
		init(prec);
}

float Sphere::ToRadians(const float& degress) {
	return (degress * 2.0f * std::numbers::pi) / 360.0f;
}

void Sphere::init(const int& prec) {
	m_numVertics = (prec + 1) * (prec + 1);
	m_numIndices = prec * prec * 6;
	m_vertices.reserve(m_numVertics);
	m_indices.reserve(m_numIndices);

	for (int i = 0; i < m_numVertics; ++i) {
		m_vertices.emplace_back(glm::vec3());
		m_texCoords.emplace_back(glm::vec2());
		m_normales.emplace_back(glm::vec3());
	}
	for (int i = 0; i < m_numIndices; ++i)
		m_indices.emplace_back(0);

	for (int i = 0; i <= prec; ++i) {
		for (int j = 0; j <= prec; ++j) {
			float y = (float)cos(ToRadians(180.0f - i * 180.0f / prec));
			float x = -(float)cos(ToRadians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));
			float z = (float)sin(ToRadians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));
			m_vertices[i * (prec + 1) + j] = glm::vec3(x * 3, y * 3, z * 3);
			m_texCoords[i * (prec + 1) + j] = glm::vec2(((float)j / prec), ((float)i / prec));
			m_normales[i * (prec + 1) + j] = glm::vec3(x, y, z);

		}
	}
	for (int i = 0; i < prec; i++) {
		for (int j = 0; j < prec; j++) {
			m_indices[6 * (i * prec + j) + 0] = i * (prec + 1) + j;
			m_indices[6 * (i * prec + j) + 1] = i * (prec + 1) + j + 1;
			m_indices[6 * (i * prec + j) + 2] = (i + 1) * (prec + 1) + j;
			m_indices[6 * (i * prec + j) + 3] = i * (prec + 1) + j + 1;
			m_indices[6 * (i * prec + j) + 4] = (i + 1) * (prec + 1) + j + 1;
			m_indices[6 * (i * prec + j) + 5] = (i + 1) * (prec + 1) + j;
		}
	}
}