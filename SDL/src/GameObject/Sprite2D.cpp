
#include "Sprite2D.h"
#include "TextureManager.h"
//Sprite2D::Sprite2D()
//{
//	Init();
//}

Sprite2D::Sprite2D(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip)
	:BaseObject(texture), m_iWidth(100), m_iHeight(50)
{
	m_flip = flip;
	Init();
	
}

Sprite2D::Sprite2D(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip, int _width, int _height)
	:BaseObject(texture), m_iWidth(_width), m_iHeight(_height)
{
	m_flip = flip;
	Init();

}

void Sprite2D::Init()
{
	// Init Camera
}

void Sprite2D::Draw(SDL_Renderer * renderer)
{
	//Get2DPosition();
	if (m_pTexture != nullptr)
	{
		m_pTexture->Render(m_position.x, m_position.y, m_iWidth, m_iHeight, m_angle, m_flip);
	}
	
}

void Sprite2D :: DrawFixedObject(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Render1(m_position.x, m_position.y, m_iWidth, m_iHeight, m_angle, m_flip);
	}
}

void Sprite2D::Update(float deltatime)
{
}

void Sprite2D::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

Vector3 Sprite2D::Get2DPosition()
{
	return Vector3(m_position.x, m_position.y, 0.0f);
}

void Sprite2D::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int Sprite2D::GetWidth()
{
	return m_iWidth;
}

int Sprite2D::GetHeight()
{
	return m_iHeight;
}

void Sprite2D::SetRotation(double angle)
{
	m_angle = angle;
}

void Sprite2D::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

std::shared_ptr<TextureManager> Sprite2D::GetTexture()
{
	return this->m_pTexture;
}

void Sprite2D::RGBEffect()
{
	if (index > 2) index = 0;
	if (r == 255 && index == 0 || g == 255 && index == 1 || b == 255 && index == 2) index++;

	if (index == 0)
	{
		if (r == 255 || r < 2) interval *= -1;
		r += interval;
	}

	if (index == 1)
	{
		if (g == 255 || g < 2) interval *= -1;
		g += interval;
	}

	if (index == 2)
	{
		if (b == 255 || b < 2) interval *= -1;
		b += interval;
	}

	this->m_pTexture->setColor(r, g, b);
}

