#pragma once
#include <string>

#include "Renderer.h"

#include "GameManager/Singleton.h"
#include "Sprite2D.h"
#include <vector>
class TextureManager  
{
private:
	SDL_Texture* m_Texture;
public:
	TextureManager();
	~TextureManager();
	void Free();
	bool Init();
	int originWidth;
	int originHeight;
	bool LoadImage(const std::string& path);
	//Render texture at given point

	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void Render(int x, int y, int width, int height, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//void RenderOriginal(int x, int y, int width, int height, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void RenderFrame(int x, int y, int width, int height, int row, int currentframe, int framecount,int numAction, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//Set blending
	void SetBlendMode(SDL_BlendMode blending);
	//Set Alpha
	void SetAlpha(Uint8 alpha);
	std::vector<SDL_Texture*> m_ListTextures;
	//Creates image from font string
	bool LoadFromRendererText(TTF_Font* font,  std::string& textureText, SDL_Color textColor);
	//SDL_Texture* GetTexture();

};


