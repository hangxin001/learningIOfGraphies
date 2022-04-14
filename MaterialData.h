#pragma once
#ifndef TESTOPENGL__MaterialData
#define TESTOPENGL__MaterialData
#include<string>
#include<vector>
#include<memory>
#include<unordered_map>
#include<array>
struct Material
{
	Material();
	Material(std::string name,
		float ambientR, float ambientG, float ambientB, float ambientAlpha, 
		float diffuseR, float diffuseG, float diffuseB, float diffuseAlpha, 
		float specularR, float specularG, float specularB, float specularAlpha,
		float shininess);
	std::string m_materialName;
	std::array<float,4> m_ambient;
	std::array<float,4> m_diffuse;
	std::array<float,4> m_specular;
	float m_shininess;

	virtual std::string GetMateriaName() { return m_materialName; }
	
	virtual std::array<float, 4> GetMaterialAmbient() { return m_ambient; }
	virtual std::array<float, 4> GetMaterialDiffuse() { return m_diffuse; }
	virtual std::array<float, 4> GetMaterialSpecular() { return m_specular; }
	
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