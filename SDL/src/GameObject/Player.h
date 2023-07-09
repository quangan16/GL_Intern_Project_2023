#pragma once
#include <iostream>
#include "TextureManager.h"


class Player
{


protected:
	Vector2 m_playerPosition;
	double m_playerRotation;
	int m_direction;
	float m_velocity;
	std::shared_ptr<TextureManager> m_playerTexture;
	std::shared_ptr<Sprite2D> playerSprite;


public:

	Player();

	Player(float _posX, float _posY,double _rotation, float _velocity, std::shared_ptr<TextureManager> _playerTexture);

	virtual ~Player();

	virtual void MoveUp(const float& _jumpForce,const float &_gravity, bool& _isJumping, bool& _isFalling, const float& _jumpBoundY, bool &_jumpBuffer, float _deltaTime) = 0;

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

	virtual float GetPlayerJumpBoundY(float _jumpHeight);

	

	//void Update(float deltaTime);
	
};

