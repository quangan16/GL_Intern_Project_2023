#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include"GameObject/Text.h"
#include "GameObject/Sound.h"
#include "GameObject/SpriteAnimation.h"
class GSCharacter :
	public GameStateBase
{
public:
	GSCharacter();
	~GSCharacter();

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
	std::shared_ptr<TextureManager>			m_texture;
	std::shared_ptr<Sprite2D>				m_background;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::shared_ptr<Text>					m_textNext;
	std::shared_ptr<Text>					m_textBack;
	SDL_Color m_textColor;
	TTF_Font* m_Font;
	std::shared_ptr<MouseButton> btnCredit;
	int score = 0;
	float time = 0.0f;

	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<MouseButton> m_btnPrev_Cube;
	std::shared_ptr<MouseButton> m_btnNext_Cube;
	std::shared_ptr<MouseButton> m_btnPrev_Ship;
	std::shared_ptr<MouseButton> m_btnNext_Ship;
	std::shared_ptr<MouseButton> m_btnPrev_Wave;
	std::shared_ptr<MouseButton> m_btnNext_Wave;
	std::shared_ptr<MouseButton> m_btnGuide;
	std::shared_ptr<MouseButton> m_btnBack;
	std::shared_ptr<MouseButton> m_btnPlay;
	std::shared_ptr<Sprite2D>				m_imglv;
	//Image Selection
	std::shared_ptr<Sprite2D>				m_img_Cube;
	std::shared_ptr<Sprite2D>				m_img_Ship;
	std::shared_ptr<Sprite2D>				m_img_Wave;

};
