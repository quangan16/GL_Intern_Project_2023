#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "GameObject/Text.h"
#include "GameObject/Player.h"
#include "GameObject/Cube.h"
#include "GameObject/GameMap.h"
class Sprite2D;
class SpriteAnimation;
class Background;



class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

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
	std::shared_ptr<GameMap> m_gameMap;
	std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::list<std::shared_ptr<Background>> m_listBackground;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<MouseButton> button;
	float time = 0.0f;
	float m_gravity = 3500.0f;

	float m_fBackground_speed = 10.f;
	Vector2 m_readyPos = Vector2(500, 700);

	std::shared_ptr<Player> m_player;
	std::shared_ptr<Sprite2D> m_playerSprite;

	//Player's jump params
	bool isJumping = false;
	bool isFalling = false;
	bool isOnGround = true;
	float jumpBoundY;
	float jumpForce = 1000.0f;
	bool jumpBuffer = false;


};

