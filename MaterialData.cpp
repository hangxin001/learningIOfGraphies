#include"MaterialData.h"
#define REGITSTMATERIAL(name,	\
						ambientR, ambientG, ambientB, ambientAlpha,	\
						diffuseR, diffuseG, diffuseB, diffuseAlpha,	\
						specularR, specularG, specularB, specularAlpha, shininess)	\
Materialptr = new Material(name,ambientR,ambientG,ambientB,ambientAlpha,diffuseR, diffuseG, diffuseB, diffuseAlpha,specularR, specularG, specularB, specularAlpha, shininess);	\
m_MateriaMap.insert(std::make_pair(name,std::make_unique<Material>(name,ambientR,ambientG,ambientB,ambientAlpha,diffuseR, diffuseG, diffuseB, diffuseAlpha,specularR, specularG, specularB, specularAlpha, shininess)));


MaterialDataManager::MaterialDataManager() {
	RegistMaterial();
}
MaterialDataManager::~MaterialDataManager() {
	//for(auto it = )
}
void MaterialDataManager::RegistMaterial() {
	Material* Materialptr = nullptr;
	REGITSTMATERIAL("gold",
		0.24725f, 0.1995f,0.0745f,1.0f,
		0.75164f,0.60648f,0.22648f,1.0f,
		0.62828f,0.5558f,0.36607f,1.0f,
		51.2f
		)
}
Material* MaterialDataManager::GetMaterial(std::string MaterialName) {
	auto it = m_MateriaMap.find(MaterialName);
	if (it != m_MateriaMap.end())
		return (it->second).get();
	return nullptr;
}
Material::Material() {
	m_materialName = "";
	m_shininess = 1.0f;
	m_ambient.reserve(4);
	m_diffuse.reserve(4);
	m_specular.reserve(4);
}
Material::Material(std::string name,
	float ambientR, float ambientG, float ambientB, float ambientAlpha,
	float diffuseR, float diffuseG, float diffuseB, float diffuseAlpha,
	float specularR, float specularG, float specularB, float specularAlpha,
	float shininess) {
	m_materialName = name;
	m_ambient = { ambientR,ambientG,ambientB,ambientAlpha };
	m_diffuse = { diffuseR,diffuseG,diffuseB,diffuseAlpha };
	m_specular = { specularR,specularG,specularB,specularAlpha };
	m_shininess = shininess;
}