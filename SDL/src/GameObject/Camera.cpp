#include"Camera.h"

void Camera::InitPosition() {
	if (m_Target != nullptr)
	{
		m_ViewBox.x = (m_Target->GetPosition().x - 650);
		m_ViewBox.y = (m_Target->GetPosition().y );
	}
}

SDL_Rect Camera::GetViewBox()
{
	return m_ViewBox;
}

void Camera :: SetPosition(Vector2 _position)
{
	m_Position = _position;
}

Vector2 Camera::GetPosition()
{
	return m_Position;
}

void Camera::SetTarget(std::shared_ptr<Sprite2D> target) // Settarget for player (-> Set origin position)
{
	m_Target = target;
}

void Camera::UpdateOnYAxis(float _deltaTime) {
	
	if (m_Target != nullptr) {
		if (m_Target->Get2DPosition().y <= m_ViewBox.y + 300) {
			if (hasGetLocationY == false) {
				newCameraPosition = Vector2(m_ViewBox.x, m_ViewBox.y - 300);
				hasGetLocationY = true;
			}
			if (m_ViewBox.y > newCameraPosition.y && hasGetLocationY == true) {
				m_ViewBox.y -= 10;
				hasGetLocationY = false;
			}
		}
		if (m_Target->Get2DPosition().y + m_Target->GetHeight() >= m_ViewBox.y + m_ViewBox.h - 300) {
			if (hasGetLocationY == false) {
				newCameraPosition = Vector2(m_ViewBox.x, m_ViewBox.y + m_ViewBox.h + 300);
				hasGetLocationY = true;
			}
			if (m_ViewBox.y + m_ViewBox.h < newCameraPosition.y && hasGetLocationY == true) {
				m_ViewBox.y += 10;
				hasGetLocationY = false;
			}
		}
	}
	
}

void Camera::Update(float deltaTime)
{

	if (m_Target != nullptr)
	{
		m_ViewBox.x = (m_Target->GetPosition().x - 650);
		
		
		//Center the camera over the dot
		
		
		//Keep the camera in bounds
		/*if (m_ViewBox.x < 0)
		{
			m_ViewBox.x = 0;
		}
		if (m_ViewBox.y < 0)
		{
			m_ViewBox.y = 0;
		}*/
		/*if (m_ViewBox.x > (2 * SCREEN_WIDTH - m_ViewBox.w))
		{
			m_ViewBox.x = (2 * SCREEN_WIDTH - m_ViewBox.w);
		}
		if (m_ViewBox.y > (2 * SCREEN_HEIGHT - m_ViewBox.h))
		{
			m_ViewBox.y = (SCREEN_HEIGHT - m_ViewBox.h);
		}*/
		m_Position = Vector2(m_ViewBox.x, m_ViewBox.y);
	}
}

//void Camera::Update2(std::shared_ptr<Player>& _player,  float deltaTime)
//{
//
//	if (m_Target != nullptr)
//	{
//		if(_player->GetPlayerPosition().x>200)
//		{
//			m_ViewBox.x = (m_Target->GetPosition().x - 400);
//			//m_ViewBox.y = (m_Target->GetPosition().y-500) ;
//
//			//Keep the camera in bounds
//			/*if (m_ViewBox.x < 0)
//			{
//				m_ViewBox.x = 0;
//			}
//			if (m_ViewBox.y < 0)
//			{
//				m_ViewBox.y = 0;
//			}*/
//			if (m_ViewBox.x > (2 * SCREEN_WIDTH - m_ViewBox.w))
//			{
//				m_ViewBox.x = (2 * SCREEN_WIDTH - m_ViewBox.w);
//			}
//			if (m_ViewBox.y > (2 * SCREEN_HEIGHT - m_ViewBox.h))
//			{
//				m_ViewBox.y = (SCREEN_HEIGHT - m_ViewBox.h);
//			}
//			m_Position = Vector2(m_ViewBox.x, m_ViewBox.y);
//		}
//		//Center the camera over the dot
//		
//	}
//}