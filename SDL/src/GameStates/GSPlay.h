#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "GameObject/Text.h"
#include "GameObject/Player.h"
#include "GameObject/Cube.h"
#include "GameObject/Ship.h"
#include "GameObject/Wave.h"
#include "GameObject/GameMap.h"
#include "GameObject/BoxCollider2D.h"
#include "GameObject/CircleCollider2D.h"
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
	void	PlayerTransform();
	int m_KeyPress;

private:
	std::shared_ptr<GameMap>						m_gameMap;
	std::shared_ptr<Text>							m_score;
	std::list<std::shared_ptr<MouseButton>>			m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>		m_listAnimation;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listTriggerAnimation;
	std::list<std::shared_ptr<Background>>			m_listBackground;
	std::shared_ptr<MouseButton>					button;
	std::shared_ptr<Sprite2D>						m_slider;
	std::shared_ptr<Player>							m_player;
	std::shared_ptr<Sprite2D>						m_playerSprite;
	std::shared_ptr<Text>							m_Process;
	double time = 0.0f;
	double m_gravity = 10000.0;

	const int PROCESS_WIDTH = 495;
	const int PROCESS_HEIGHT = 10;
	const int PROCESS_PADDING = 5;
	float maxProcess = 100.0f;
	float currentProcess = 0.0f;
	int processBarWidth;

	const int m_fBackground_speed = 10.f;
	Vector2 m_readyPos = Vector2(500, 700);

	std::shared_ptr<SpriteAnimation> m_trigger1;
	

	//Player's jump params
	/*bool isJumping = false;
	bool isFalling = true;
	bool isOnGround = false;
	double jumpForce = 3000.0;*/
	bool jumpBuffer = false;

	//Ship's param
	

	//Collider
	std::vector<std::shared_ptr<BoxCollider2D>> m_boxColliderList;
	std::vector<std::shared_ptr<CircleCollider2D>> m_circleColliderList;
	std::shared_ptr<BoxCollider2D> m_playerCollider;
	std::shared_ptr<BoxCollider2D> m_collider1;
	std::shared_ptr<BoxCollider2D> m_collider2;

	std::shared_ptr<SDL_Color> m_color;

	//std::shared_ptr<Player> m_ground;

	bool m_onButtonPressed = false;
	bool m_onButtonDown = false;
	bool m_onButtonUp = false;

};

