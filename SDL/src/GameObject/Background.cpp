#include "Background.h"
#include "TextureManager.h"
#include "Define.h"
Background::Background(std::shared_ptr<TextureManager> texture, float speed, SDL_RendererFlip flip)
	:Sprite2D(texture,flip)
{
	m_fBackground_speed = speed;
	Init();
}

void Background::Init()
{

}


void Background::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Render(m_position.x, m_position.y, m_iWidth, m_iHeight, m_angle, m_flip);
	}
}

void Background::Update(float deltaTime)
{
	
}

void Background::SetSpeed(float speed)
{
	m_fBackground_speed = speed;
}

float Background::GetSpeed()
{
	return this->m_fBackground_speed;
}

void Background::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

Vector3 Background::Get2DPosition()
{
	return Vector3(m_position.x, m_position.y, 0.0f);
}

void Background::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int Background::GetWidth()
{
	return m_iWidth;
}

int Background::GetHeight()
{
	return m_iHeight;
}

void Background::SetRotation(double angle)
{
	m_angle = angle;
}

void Background::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}


std::tuple<std::shared_ptr<Background>, std::shared_ptr<Background>> Background::MovingBackGround(std::shared_ptr<Background> m_background, std::shared_ptr<Background> m_background_2)
{
	m_background->Set2DPosition(m_background->Get2DPosition().x - m_fBackground_speed, 0);
	m_background_2->Set2DPosition(m_background_2->Get2DPosition().x - m_fBackground_speed, 0);

	if (m_background->Get2DPosition().x <= -SCREEN_WIDTH)
	{
		m_background->Set2DPosition(m_background_2->Get2DPosition().x + (float)SCREEN_WIDTH, 0);
	}

	if (m_background_2->Get2DPosition().x <= -SCREEN_WIDTH)
	{
		m_background_2->Set2DPosition(m_background->Get2DPosition().x + (float)SCREEN_WIDTH, 0);
	}
	auto res = std::make_tuple(m_background, m_background_2);

	return res;
}
