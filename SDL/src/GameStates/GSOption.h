#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
class Sprite2D;
class SpriteAnimation;

class GSOption :
	public GameStateBase
{
public:
	GSOption();
	~GSOption();

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
	std::shared_ptr<Sprite2D>	m_background;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<MouseButton> button;
	std::shared_ptr<MouseButton> m_backButton;
	float time = 0.0f;
	//const int VOLUME_WIDTH = 200;
	//const int VOLUME_HEIGHT = 20;
	//const int VOLUME_PADDING = 10;
	//int maxVolume = 100;
	//int currentVolume = 50;
	//int volumeBarWidth;
	//float m_Velocity = 10.0f;

	const int SLIDER_WIDTH = 200;
	const int SLIDER_HEIGHT = 20;
	const int SLIDER_PADDING = 10;
	const int INITIAL_VOLUME = 50;
	int volume = INITIAL_VOLUME;
};

