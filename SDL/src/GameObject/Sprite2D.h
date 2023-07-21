#pragma once
#include"BaseObject.h"
#include "Define.h"

class Sprite2D : public BaseObject
{
protected:
	int m_iWidth;
	int m_iHeight;
	SDL_RendererFlip m_flip;

public:
	Sprite2D() : BaseObject(), m_iWidth(0), m_iHeight(0) {}
	Sprite2D(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
	Sprite2D( std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip, int _width, int _height);
	void Init() override;
	void Draw(SDL_Renderer * renderer) override;
	void DrawFixedObject(SDL_Renderer* renderer);
	void Update(float deltatime) override;
	void Set2DPosition(float x, float y);
	Vector3		Get2DPosition();
	void SetSize(int width, int height);
	int GetWidth();
	int GetHeight();
	void SetRotation(double angle);
	void SetFlip(SDL_RendererFlip flip);
	std::shared_ptr<TextureManager> GetTexture();
	void RGBEffect();
};

