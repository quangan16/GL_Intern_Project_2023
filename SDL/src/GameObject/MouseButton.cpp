#include "MouseButton.h"
#include "TextureManager.h"
MouseButton::MouseButton() : Sprite2D(), m_pBtClick(nullptr)
{
	m_position.x= 0;
	m_position.y = 0;
}

MouseButton::MouseButton(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip)
	: Sprite2D(texture,flip), m_pBtClick(nullptr)
{
}

bool MouseButton::HandleTouchEvent(SDL_Event* e)
{
	//If mouse event happened (clicked/ release...
	if (e->type == SDL_MOUSEBUTTONDOWN )//|| e->type == SDL_MOUSEBUTTONUP) e->type == SDL_MOUSEMOTION || 
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		// Check if mouse is in button
		bool inside = true;
		//Mouse is left/right above/below of the button
		if (x < m_position.x || x > m_position.x + m_iWidth|| y < m_position.y || y > m_position.y + m_iHeight)
		{
			inside = false;
		}
		// Mouse is outside button
		if(inside)
		{
			// Only perform click action when the same button was pressed down and released
			m_pBtClick();
		}
		return inside;
	}
	return false;
}


void MouseButton::Draw(SDL_Renderer * renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Render(m_position.x, m_position.y, m_iWidth, m_iHeight);
	}
}

void MouseButton::SetOnClick(std::function<void(void)> pBtClick)
{
	m_pBtClick = pBtClick;
}





