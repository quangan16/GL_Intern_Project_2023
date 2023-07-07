#pragma once
#include <iostream>
#include "TextureManager.h"


class Player
{


protected:
	Vector2 m_playerPosition;
	int direction;
	float velocity;
	std::shared_ptr<TextureManager> m_playerTexture;
	std::shared_ptr<Sprite2D> playerSprite;


public:

	Player();

	Player(float _posX, float _posY, float _velocity, std::shared_ptr<TextureManager> _playerTexture);

	virtual ~Player();

	virtual void MoveUp() = 0;

	Vector2 GetPlayerPosition();

	void SetPlayerPosition(float _x, float _y);

	float GetPlayerVelocity();

	void SetPlayerVelocity(float _velocity);

	virtual void SetPlayerSprite(const int &_width,const int &_height, const std::shared_ptr<Sprite2D> &_playerSprite);

	void SetDirectionY(int _direction);

	int GetDirectionY();

	void UpdatePlayerSpritePos(const std::shared_ptr<Sprite2D>& _playerSprite);

	void UpdatePlayerSpriteRotation(const std::shared_ptr<Sprite2D>& _playerSprite);

	void RunIntoScene(const Vector2 &endPos, float _deltaTime);

	//void Update(float deltaTime);
	
};

