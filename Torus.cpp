#include"Torus.h"
#include<iostream>

Torus::Torus(const float& innerRadius, const float& outerRadius, const int& prec){
	m_numVertices = 0;
	m_numIndices = 0;
	m_prec = 0;
	m_inner = 0;
	m_outer = 0;
	init(innerRadius, outerRadius, prec);
}

void Torus::init(const float& innerRadius, const float& outerRadius, const int& prec) {
	m_numVertices = (prec + 1) * (prec + 1);
	m_numIndices = prec * prec * 6;
	m_prec = prec;
	m_inner = innerRadius;
	m_outer = outerRadius;
	for (int i = 0; i < m_numVertices; i++) { m_vertices.push_back(glm::vec3()); }
	for (int i = 0; i < m_numVertices; i++) { m_texCoords.push_back(glm::vec2()); }
	for (int i = 0; i < m_numVertices; i++) { m_normals.push_back(glm::vec3()); }
	for (int i = 0; i < m_numVertices; i++) { m_sTangents.push_back(glm::vec3()); }
	for (int i = 0; i < m_numVertices; i++) { m_tTangents.push_back(glm::vec3()); }
	for (int i = 0; i < m_numIndices; i++) { m_indices.push_back(0); }
	
	// �����һ����
		for (int i = 0; i < prec + 1; i++) {
			float amt = ToRadians(i * 360.0f / prec);
			// ��ԭ����ת�㣬�γɻ���Ȼ�����������ƶ�
			glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 0.0f, 1.0f));
			glm::vec3 initPos(rMat * glm::vec4(m_outer, 0.0f, 0.0f, 1.0f));
			m_vertices[i] = glm::vec3(initPos + glm::vec3(m_inner, 0.0f, 0.0f));

			// Ϊ���ϵ�ÿ�����������������
			m_texCoords[i] = glm::vec2(0.0f, ((float)i / (float)prec));

			// �����������ͷ���������һ������������Z����ת��Y��
			rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 0.0f, 1.0f));
			m_tTangents[i] = glm::vec3(rMat * glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));
			m_sTangents[i] = glm::vec3(glm::vec3(0.0f, 0.0f, -1.0f));   // �ڶ����������� -Z ��
			m_normals[i] = glm::cross(m_tTangents[i], m_sTangents[i]);      // ���ǵĲ�˻����Ƿ�����
		}

		// ��Y����ת������Ǹ������γ������Ļ�
		for (int ring = 1; ring < prec + 1; ring++) {
			for (int vert = 0; vert < prec + 1; vert++) {

				// ��Y����ת����Ǹ����Ķ�������
				float amt = (float)(ToRadians(ring * 360.0f / prec));
				glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
				m_vertices[ring * (prec + 1) + vert] = glm::vec3(rMat * glm::vec4(m_vertices[vert], 1.0f));

				// �����»��������������
				m_texCoords[ring * (prec + 1) + vert] = glm::vec2((float)ring * 2.0f / (float)prec, m_texCoords
					[vert].t);
				if (m_texCoords[ring * (prec + 1) + vert].s > 1.0) m_texCoords[ring * (prec + 1) + vert].s -= 1.0f;

				// ��Y����ת�������͸�������
				rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
				m_sTangents[ring * (prec + 1) + vert] = glm::vec3(rMat * glm::vec4(m_sTangents[vert], 1.0f));
				rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
				m_tTangents[ring * (prec + 1) + vert] = glm::vec3(rMat * glm::vec4(m_tTangents[vert], 1.0f));

				// ��Y����ת������
				rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
				m_normals[ring * (prec + 1) + vert] = glm::vec3(rMat * glm::vec4(m_normals[vert], 1.0f));
			}
		}

		// ���������������������Σ���������������
		for (int ring = 0; ring < prec; ring++) {
			for (int vert = 0; vert < prec; vert++) {
				m_indices[((ring * prec + vert) * 2) * 3 + 0] = ring * (prec + 1) + vert;
				m_indices[((ring * prec + vert) * 2) * 3 + 1] = (ring + 1) * (prec + 1) + vert;
				m_indices[((ring * prec + vert) * 2) * 3 + 2] = ring * (prec + 1) + vert + 1;
				m_indices[((ring * prec + vert) * 2 + 1) * 3 + 0] = ring * (prec + 1) + vert + 1;
				m_indices[((ring * prec + vert) * 2 + 1) * 3 + 1] = (ring + 1) * (prec + 1) + vert;
				m_indices[((ring * prec + vert) * 2 + 1) * 3 + 2] = (ring + 1) * (prec + 1) + vert + 1;
			}
		}

}