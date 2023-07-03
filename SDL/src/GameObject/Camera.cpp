#include"Camera.h"

SDL_Rect Camera::GetViewBox()
{
	return m_ViewBox;
}

Vector2 Camera::GetPosition()
{
	return m_Position;
}

void Camera::SetTarget(std::shared_ptr<SpriteAnimation> target) // Settarget for player (-> Set origin position)
{
	m_Target = target;
}

void Camera::Update(float deltaTime)
{
	if (m_Target != nullptr)
	{
		//Center the camera over the dot
		m_ViewBox.x = (m_Target->Get2DPosition().x  - SCREEN_WIDTH / 2) ;
		m_ViewBox.y = (m_Target->Get2DPosition().y  - SCREEN_HEIDHT / 2) ;
		
		//Keep the camera in bounds
		if (m_ViewBox.x < 0)
		{
			m_ViewBox.x = 0;
		}
		if (m_ViewBox.y < 0)
		{
			m_ViewBox.y = 0;
		}
		if (m_ViewBox.x > (2 * SCREEN_WIDTH - m_ViewBox.w))
		{
			m_ViewBox.x = (2 * SCREEN_WIDTH - m_ViewBox.w);
		}
		if (m_ViewBox.y > (2 * SCREEN_HEIDHT - m_ViewBox.h))
		{
			m_ViewBox.y = (SCREEN_HEIDHT - m_ViewBox.h);
		}
		m_Position = Vector2(m_ViewBox.x, m_ViewBox.y);
	}
}
