#pragma once
#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include <Text.h>
class Sprite2D;
class SpriteAnimation;

class GSGuide :
	public GameStateBase
{
public:
	GSGuide();
	~GSGuide();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	int m_KeyPress;

private:
	SDL_Color m_textColor;
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Sprite2D>	m_guide_Ship;
	std::shared_ptr<Sprite2D>	m_guide_Cube;

	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<MouseButton>	button;
	std::shared_ptr<MouseButton>	m_buttonBack;
};

