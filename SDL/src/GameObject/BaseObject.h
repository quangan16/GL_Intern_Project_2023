#pragma once
#include "CMath.h"
#include <memory>
#include "SDL.h"
#include <SDL_image.h>
#include "SDL_ttf.h"
class TextureManager;
class BaseObject
{
protected:
	Vector3 m_position;
	Vector3 m_scale;
	double m_angle = 0.0; // default angle
	SDL_RendererFlip m_flip = SDL_FLIP_NONE;
	std::shared_ptr<TextureManager> m_pTexture;
public:
	BaseObject() : m_pTexture(nullptr), m_position(Vector3(0.0f, 0.0f, 0.0f)), m_scale(Vector3(1.0f, 1.0f, 1.0f)) {}
	BaseObject(std::shared_ptr<TextureManager> texture)
		:m_pTexture(texture), m_position(Vector3(0.0f, 0.0f, 0.0f)) , m_scale(Vector3(1.0f, 1.0f, 1.0f) ){}
	virtual void Init() = 0;
	virtual void Draw(SDL_Renderer* renderer) = 0;
	virtual void Update(float deltatime) = 0;
	void SetPosition(Vector3 position) { m_position = position; }
	Vector3 GetPosition() { return m_position; }
	void SetTexture(std::shared_ptr<TextureManager> texture) { m_pTexture = texture; }
	 
};

 