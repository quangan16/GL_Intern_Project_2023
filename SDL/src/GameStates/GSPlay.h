#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "GameObject/Text.h"
#include "GameObject/Player.h"
#include "GameObject/Cube.h"
#include "GameObject/GameMap.h"
#include "GameObject/BoxCollider2D.h"
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
	double m_gravity = 3500.0;

	const int PROCESS_WIDTH = 500;
	const int PROCESS_HEIGHT = 20;
	const int PROCESS_PADDING = 10;
	float maxProcess = 100.0f;
	float currentProcess = 0.0f;
	float processBarWidth;

	float m_fBackground_speed = 10.f;
	Vector2 m_readyPos = Vector2(500, 700);

	std::shared_ptr<Cube> m_player;
	std::shared_ptr<Sprite2D> m_playerSprite;

	//Player's jump params
	bool isJumping = false;
	bool isFalling = true;
	bool isOnGround = false;
	double jumpForce = 1300.0;
	bool jumpBuffer = false;


	//Collider
	std::shared_ptr<BoxCollider2D> m_playerCollider;
	std::shared_ptr<BoxCollider2D> m_collider1;
	std::shared_ptr<BoxCollider2D> m_collider2;

	std::shared_ptr<SDL_Color> m_color;

	//std::shared_ptr<Player> m_ground;

};

