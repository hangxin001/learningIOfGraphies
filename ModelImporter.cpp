#include"ModelImporter.h"
#include<sstream>
#include<iostream>
#include<filesystem>
#include<fstream>
ImportedModel::ImportedModel(const char* filePath) {
    ModelImporter modelImporter = ModelImporter();
    modelImporter.parseOBJ(filePath);           // ʹ��modelImporter��ȡ������Ϣ
    m_numVertices = modelImporter.getNumVertices();
    std::vector<float> verts = modelImporter.getVertices();
    std::vector<float> tcs = modelImporter.getTextureCoordinates();
    std::vector<float> normals = modelImporter.getNormals();

    for (int i = 0; i < m_numVertices; i++) {
        m_vertices.push_back(glm::vec3(verts[i * 3], verts[i * 3 + 1], verts[i * 3 + 2]));
        m_texCoords.push_back(glm::vec2(tcs[i * 2], tcs[i * 2 + 1]));
        m_normalVecs.push_back(glm::vec3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]));
    }
}
ImportedModel::ImportedModel(const std::string& filePath) {
    ModelImporter modelImporter = ModelImporter();
    modelImporter.parseOBJ(filePath.c_str());           // ʹ��modelImporter��ȡ������Ϣ
    m_numVertices = modelImporter.getNumVertices();
    std::vector<float> verts = modelImporter.getVertices();
    std::vector<float> tcs = modelImporter.getTextureCoordinates();
    std::vector<float> normals = modelImporter.getNormals();

    for (int i = 0; i < m_numVertices; i++) {
        m_vertices.push_back(glm::vec3(verts[i * 3], verts[i * 3 + 1], verts[i * 3 + 2]));
        m_texCoords.push_back(glm::vec2(tcs[i * 2], tcs[i * 2 + 1]));
        m_normalVecs.push_back(glm::vec3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]));
    }
}
void ModelImporter::parseOBJ(const std::string& filePath) {
    parseOBJ(filePath.c_str());
}
void ModelImporter::parseOBJ(const char* filePath) {
    using namespace std;
    float x, y, z;
    string content;
    ifstream fileStream(filePath, ios::in);
    string line = "";
    while (!fileStream.eof()) {
        getline(fileStream, line);
        if (line.compare(0, 2, "v ") == 0) {           // ����λ�ã�"v"�������
            stringstream ss(line.erase(0, 1));
            ss >> x; ss >> y; ss >> z;                  // ��ȡ����λ����ֵ
            m_vertVals.push_back(x);
            m_vertVals.push_back(y);
            m_vertVals.push_back(z);
        }

        if (line.compare(0, 2, "vt") == 0) {           // �������꣨"vt"�������
            stringstream ss(line.erase(0, 2));
            ss >> x; ss >> y;                           // ��ȡ����������ֵ
            m_stVals.push_back(x);
            m_stVals.push_back(y);
        }
        if (line.compare(0, 2, "vn") == 0) {           // ���㷨������"vn"�������
            stringstream ss(line.erase(0, 2));
            ss >> x; ss >> y; ss >> z;                  // ��ȡ��������ֵ
            m_normVals.push_back(x);
            m_normVals.push_back(y);
            m_normVals.push_back(z);
        }
        if (line.compare(0, 1, "f") == 0) {            // �������棨"f"�������
            string oneCorner, v, t, n;
            stringstream ss(line.erase(0, 2));
            for (int i = 0; i < 3; i++) {
                getline(ss, oneCorner, ' ');             // ��ȡ������������
                stringstream oneCornerSS(oneCorner);
                getline(oneCornerSS, v, '/');
                getline(oneCornerSS, t, '/');
                getline(oneCornerSS, n, '/');

                int vertRef = (stoi(v) - 1) * 3;         // "stoi"���ַ���ת��Ϊ����
                int tcRef = (stoi(t) - 1) * 2;
                int normRef = (stoi(n) - 1) * 3;

                m_triangleVerts.push_back(m_vertVals[vertRef]);     // ������������
                m_triangleVerts.push_back(m_vertVals[vertRef + 1]);
                m_triangleVerts.push_back(m_vertVals[vertRef + 2]);

                m_textureCoords.push_back(m_stVals[tcRef]);         // ����������������
                m_textureCoords.push_back(m_stVals[tcRef + 1]);

                m_normals.push_back(m_normVals[normRef]);           // ������������
                m_normals.push_back(m_normVals[normRef + 1]);
                m_normals.push_back(m_normVals[normRef + 2]);
            }
        }
    }
}