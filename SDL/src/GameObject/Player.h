#pragma once
#include <iostream>

#include "Background.h"
#include "TextureManager.h"
#include "BoxCollider2D.h"


class Ball;
class Cube;
class Ship;
class Wave;
class Spider;

enum PlayerForm {
	CUBE,
	SHIP,
	WAVE,
	BALL,
	ROBOT,
	SPIDER
};

class Player
{
public:
	//PlayerActionState
	bool m_isJumping;
	bool m_isFalling;
	bool m_isOnGround;
	double m_jumpForce;
	bool m_isAlive;
	bool m_jumpBuffer = false;
	bool m_changedState = false;

	std::shared_ptr<SpriteAnimation> m_playerDieEffect;
	std::shared_ptr<SpriteAnimation> m_playerTrailEffect;
	std::shared_ptr<SpriteAnimation> m_playerJumpEffect;

protected:
	PlayerForm m_playerForm;
	Vector2 m_playerPosition;
	double m_playerRotation;
	int m_direction;
	double m_velocity;
	float m_playerSpeed;
	double max_velocity = 3000;
	

	std::shared_ptr<TextureManager> m_playerTexture;
	std::shared_ptr<Sprite2D> m_playerSprite;
	std::shared_ptr<SpriteAnimation> m_playerAnimation;
	


	std::shared_ptr<BoxCollider2D> m_playerCollider;


public:

	Player();

	Player(Vector2 _position ,double _rotation, int _direction, double _velocity);

	virtual ~Player();

	virtual void MoveUp(const double&_gravity,const bool& m_onButtonPressed, float _deltaTime) = 0;

	virtual void Rotate(double _angle, float _deltaTime) = 0;

	Vector2 GetPlayerPosition();

	void SetPlayerPosition(float _x, float _y);

	float GetPlayerVelocity();

	void SetPlayerVelocity(float _velocity);

	const double& GetPlayerRotation();

	virtual void SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) ;

	virtual std::shared_ptr<Sprite2D> GetPlayerSprite() = 0;

	void SetDirectionY(int _direction);

	int GetDirectionY();

	void UpdatePlayerSprite();

	void UpdatePlayerSpriteRotation(const std::shared_ptr<Sprite2D>& _playerSprite);

	void RunIntoScene(const Vector2 &endPos, float _deltaTime);

	virtual void ApplyGravity(const double& _gravity, float _deltaTime) = 0;

	void UpdatePlayerPos(float& _deltaTime);

	virtual void FixRotationOnGround(const float& deltaTime) = 0;

	virtual const std::shared_ptr<BoxCollider2D> GetCollider() const = 0;

	void UpdatePlayerColliderState();

	virtual void OnGround() = 0;

	bool OnCollisionStay(std::shared_ptr<BoxCollider2D> otherCollider, std::shared_ptr<Player> &_player);

	void JumpTrigger();

	void OnCollisionTrigger(std::shared_ptr<CircleCollider2D> _otherCollider, double& _gravity, const float& _deltaTime);

	std::shared_ptr<TextureManager> GetPlayerTexture();

	std::shared_ptr<Cube> TransformToCube();

	std::shared_ptr<Ship> TransformToShip();

	std::shared_ptr<Wave> TransformToWave();

	std::shared_ptr<Ball>TransformToBall();

	std::shared_ptr<Spider>TransformToSpider();

	std::shared_ptr<SpriteAnimation> GetPlayerAnimation();
		
	void UpdatePlayerAnimation();

	void FixCollisionOverlapsOnSurface(std::shared_ptr<BoxCollider2D> otherCollider);
	void FixCollisionOverlapsUnderSurface(std::shared_ptr<BoxCollider2D> _otherCollider);
	void Die(std::shared_ptr<Background>& _bg, std::shared_ptr<Sound>& _bgSound, std::shared_ptr<Sound>& _DieSfx, float& dieTime, float _waitTime);
	//void Update(float deltaTime);
	
};



