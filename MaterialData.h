#pragma once
#ifndef __TESTOPENGL__MaterialData__
#define __TESTOPENGL__MaterialData__
#include<string>
#include<vector>
#include<memory>
#include<unordered_map>
struct Material
{
	Material();
	Material(std::string name,
		float ambientR, float ambientG, float ambientB, float ambientAlpha, 
		float diffuseR, float diffuseG, float diffuseB, float diffuseAlpha, 
		float specularR, float specularG, float specularB, float specularAlpha,
		float shininess);
	std::string m_materialName;
	std::vector<float> m_ambient;
	std::vector<float> m_diffuse;
	std::vector<float> m_specular;
	float m_shininess;

	virtual std::string GetMateriaName() { return m_materialName; }
	virtual std::vector<float> GetMaterialAmbient() { return m_ambient; }
	virtual std::vector<float> GetMaterialDiffuse() { return m_diffuse; }
	virtual std::vector<float> GetMaterialSpecular() { return m_specular; }
	virtual float GetMaterialShiniess() { return m_shininess; }
};
class MaterialDataManager {
public:
	MaterialDataManager();
	~MaterialDataManager();
	MaterialDataManager(Material&) = delete;
private:
	std::unordered_map<std::string,std::unique_ptr<Material>> m_MateriaMap;
public:
	Material* GetMaterial(std::string MaterialName);
private:
	void RegistMaterial();
};
#endif