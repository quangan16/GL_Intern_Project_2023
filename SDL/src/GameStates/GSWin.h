#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include"GameObject/Text.h"
#include "GameObject/Sound.h"
#include "GameObject/SpriteAnimation.h"
class GSWin :
	public GameStateBase
{
public:
	GSWin();
	~GSWin();

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
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::shared_ptr<Sprite2D>				m_gameTitle;
	SDL_Color m_textColor;
	TTF_Font* m_Font;
	int score = 0;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<MouseButton> m_btnGuide;
	std::shared_ptr<MouseButton> m_btnWindow;
	std::shared_ptr<MouseButton> m_btnCharacter_Selection;
	std::shared_ptr<MouseButton> m_btnPlay;
	std::shared_ptr<MouseButton> m_btnOption;
};