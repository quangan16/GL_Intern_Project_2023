#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include"GameObject/Text.h"
#include "GameObject/Sound.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/IOFile.h"
class GSLevel :
	public GameStateBase
{
public:
	GSLevel();
	~GSLevel();

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

private:
	std::shared_ptr<Sprite2D>				m_background;
	std::shared_ptr<Sprite2D>				m_levelPickCanvas;
	std::shared_ptr<Sprite2D>				m_slider;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::shared_ptr<Text>					m_textGameName;
	SDL_Color m_textColor;
	TTF_Font* m_Font;
	std::shared_ptr<MouseButton> btnCredit;
	int score = 0;
	float time = 0.0f;
	const int PROCESS_WIDTH = 1000;
	const int PROCESS_HEIGHT = 30;
	const int PROCESS_PADDING = 5;
	float maxProcess = 100.0f;
	float currentProcess = 0.0f;
	float processBarWidth;

	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<MouseButton> m_btnPrev;
	std::shared_ptr<MouseButton> m_btnNext;
	std::shared_ptr<MouseButton> m_btnGuide;
	std::shared_ptr<MouseButton> m_btnBack;
	std::shared_ptr<MouseButton> m_btnPlay;
};
