#pragma once
#include "SDL.h"
#include <string>
#include <memory>
#include "TextureManager.h"
class Text: public Sprite2D
{
public:
	Text(std::string fontPath,  SDL_Color textColor);
	void		Init() override;
	void		Draw(SDL_Renderer* renderer) override;
	void		Update(float deltatime) override;
	void LoadFromRenderText(std::string textureText);
private:
	//std::shared_ptr<TextureManager> m_Texture;
	std::string m_TextureText;
	SDL_Color  m_TextColor;
	TTF_Font*  m_Font;
};
