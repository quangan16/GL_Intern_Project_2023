#include "ResourceManagers.h"

ResourceManagers::ResourceManagers()
{
	std::string dataPath = "Data/";
	m_TexturePath = dataPath + "Textures/";
	
}

ResourceManagers::~ResourceManagers()
{
}
void ResourceManagers::AddTexture(const std::string& name)
{
	auto it = m_MapTexture.find(name);
	if (it != m_MapTexture.end())
	{
		return;
	}
	std::shared_ptr<TextureManager> texture = std::make_shared<TextureManager>();
	std::string file = m_TexturePath + name;
	texture->LoadImage(file.c_str());
	m_MapTexture.insert(std::pair<std::string, std::shared_ptr<TextureManager>>(name, texture));
}

void ResourceManagers::AddFont(const std::string& name)
{
	
}

void ResourceManagers::RemoveTexture(const std::string& name)
{
}

void ResourceManagers::RemoveFont(const std::string& name)
{
}

std::shared_ptr<TextureManager> ResourceManagers::GetTexture(const std::string& name)
{
	auto it = m_MapTexture.find(name);
	if (it != m_MapTexture.end())
	{
		return it->second;
	}
	std::shared_ptr<TextureManager> texture = std::make_shared<TextureManager>();
	std::string file = m_TexturePath + name;
	texture->LoadImage(file.c_str());
	m_MapTexture.insert(std::pair<std::string, std::shared_ptr<TextureManager>>(name, texture));
	return texture;
}


