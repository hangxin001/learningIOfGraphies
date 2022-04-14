#include"ModelImporter.h"
#include<sstream>
#include<iostream>
#include<filesystem>
#include<fstream>
ImportedModel::ImportedModel(const char* filePath) {
    ModelImporter modelImporter = ModelImporter();
    modelImporter.parseOBJ(filePath);           // 使用modelImporter获取顶点信息
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
    modelImporter.parseOBJ(filePath.c_str());           // 使用modelImporter获取顶点信息
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
        if (line.compare(0, 2, "v ") == 0) {           // 顶点位置（"v"的情况）
            stringstream ss(line.erase(0, 1));
            ss >> x; ss >> y; ss >> z;                  // 提取顶点位置数值
            m_vertVals.push_back(x);
            m_vertVals.push_back(y);
            m_vertVals.push_back(z);
        }

        if (line.compare(0, 2, "vt") == 0) {           // 纹理坐标（"vt"的情况）
            stringstream ss(line.erase(0, 2));
            ss >> x; ss >> y;                           // 提取纹理坐标数值
            m_stVals.push_back(x);
            m_stVals.push_back(y);
        }
        if (line.compare(0, 2, "vn") == 0) {           // 顶点法向量（"vn"的情况）
            stringstream ss(line.erase(0, 2));
            ss >> x; ss >> y; ss >> z;                  // 提取法向量数值
            m_normVals.push_back(x);
            m_normVals.push_back(y);
            m_normVals.push_back(z);
        }
        if (line.compare(0, 1, "f") == 0) {            // 三角形面（"f"的情况）
            string oneCorner, v, t, n;
            stringstream ss(line.erase(0, 2));
            for (int i = 0; i < 3; i++) {
                getline(ss, oneCorner, ' ');             // 提取三角形面引用
                stringstream oneCornerSS(oneCorner);
                getline(oneCornerSS, v, '/');
                getline(oneCornerSS, t, '/');
                getline(oneCornerSS, n, '/');

                int vertRef = (stoi(v) - 1) * 3;         // "stoi"将字符串转化为整型
                int tcRef = (stoi(t) - 1) * 2;
                int normRef = (stoi(n) - 1) * 3;

                m_triangleVerts.push_back(m_vertVals[vertRef]);     // 构建顶点向量
                m_triangleVerts.push_back(m_vertVals[vertRef + 1]);
                m_triangleVerts.push_back(m_vertVals[vertRef + 2]);

                m_textureCoords.push_back(m_stVals[tcRef]);         // 构建纹理坐标向量
                m_textureCoords.push_back(m_stVals[tcRef + 1]);

                m_normals.push_back(m_normVals[normRef]);           // 法向量的向量
                m_normals.push_back(m_normVals[normRef + 1]);
                m_normals.push_back(m_normVals[normRef + 2]);
            }
        }
    }
}