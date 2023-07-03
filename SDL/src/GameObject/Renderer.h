#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameManager/Singleton.h"
#include <SDL_ttf.h>
class Renderer :public CSingleton<Renderer>{
public:
	Renderer();
	~Renderer();
	bool Init();
	SDL_Window* GetWindow();
	void SetWindow(SDL_Window* mWindow);
	SDL_Renderer* GetRenderer();
	void SetRenderer(SDL_Renderer* mRenderer);
	//void SetTTFFont(TTF_Font* mFont);
	//TTF_Font* GetFont();
	SDL_Rect* GetSpriteClips();
	void SetSpriteClips(SDL_Rect** mSpriteClips);
private:
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	TTF_Font* gFont;
	 int WALKING_ANIMATION_FRAMES ;
	SDL_Rect* gSpriteClips[4];
};