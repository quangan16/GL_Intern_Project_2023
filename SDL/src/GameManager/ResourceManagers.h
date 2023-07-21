#pragma once
#include <map>
#include "Singleton.h"

#include "GameObject/TextureManager.h"


class ResourceManagers : public CSingleton<ResourceManagers>
{
public:
	ResourceManagers();
	~ResourceManagers();


	void AddTexture(const std::string& name);
	void AddFont(const std::string& name);

	void RemoveSound(const std::string& name) {};
	void RemoveTexture(const std::string& name);
	void RemoveFont(const std::string& name);

	std::shared_ptr<TextureManager> GetTexture(const std::string& name);

	bool WriteToFile(const char* _fileName);
	void ReadFromFile(const char* _fileName);
	static bool isMuted;
private:
	std::map<std::string, std::shared_ptr<TextureManager>> m_MapTexture;
	std::string m_ShaderPath;
	std::string m_TexturePath;
	std::string m_ModelsPath;
	std::string m_FontPath;

	//Sound
	std::string m_SoundPath;
	const char* m_fileName;
};

