#pragma once
#include <iostream>
#include "TextureManager.h"
#include "BoxCollider2D.h"
#include <memory>

class Player
{
public:
	//PlayerActionState
	bool m_isJumping;
	bool m_isFalling;
	bool m_isOnGround;
	double m_jumpForce;
	bool m_isAlive;

protected:
	Vector2 m_playerPosition;
	double m_playerRotation;
	int m_direction;
	double m_velocity;
	float m_playerSpeed = PLAYER_SPEED;
	double max_velocity = 3000;
	

	std::shared_ptr<TextureManager> m_playerTexture;
	std::shared_ptr<Sprite2D> m_playerSprite;

	std::shared_ptr<BoxCollider2D> m_playerCollider;


public:

	Player();

	Player(Vector2 _position ,double _rotation, int _direction, double _velocity, std::shared_ptr<TextureManager> _playerTexture);

	virtual ~Player();

	virtual void MoveUp(const double&_gravity,const bool& m_onButtonPressed, bool &_jumpBuffer, float _deltaTime) = 0;

	virtual void Rotate(double _angle, float _deltaTime) = 0;

	Vector2 GetPlayerPosition();

	void SetPlayerPosition(float _x, float _y);

	float GetPlayerVelocity();

	void SetPlayerVelocity(float _velocity);

	virtual void SetPlayerSprite(const int &_width,const int &_height, const std::shared_ptr<Sprite2D> &_playerSprite);

	void SetDirectionY(int _direction);

	int GetDirectionY();

	void UpdatePlayerSprite(const std::shared_ptr<Sprite2D>& _playerSprite);

	void UpdatePlayerSpriteRotation(const std::shared_ptr<Sprite2D>& _playerSprite);

	void RunIntoScene(const Vector2 &endPos, float _deltaTime);

	virtual void ApplyGravity(const double& _gravity, float _deltaTime) = 0;

	void UpdatePlayerPos(float& _deltaTime, Map &map_data);

	virtual void FixRotationOnGround(const float& deltaTime) = 0;

	virtual const std::shared_ptr<BoxCollider2D> GetCollider() const = 0;

	void UpdatePlayerColliderState();

	virtual void OnGround() = 0;

	bool OnCollisionStay(std::shared_ptr<BoxCollider2D> otherCollider);

	void CheckToMap(Map& map_data, float& _deltaTime);
	
	void FixCollisionOverlaps(std::shared_ptr<BoxCollider2D> otherCollider);

	void Die();
	//void Update(float deltaTime);
	
};

enum PlayerForm {
	CUBE,
	SHIP,
	ARROW,
	WHEEL,
	ROBOT
};

