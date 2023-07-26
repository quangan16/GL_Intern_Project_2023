#pragma once
#include "SDL_mixer.h"
#include <string>
#include "Define.h"
class Sound
{
public:
	Sound(std::string pathMusic);
	~Sound();
	bool Init();
	void PlaySound();
	void PlaySoundOnce();
	void PauseSound();
	void ResumeSound();
	void StopSound();
	void LoadSound(std::string pathMusic);
	void Free();
	bool m_isMuted;
private:
	std::string m_PathMusic;
	Mix_Music* m_Music = NULL;
	
};
