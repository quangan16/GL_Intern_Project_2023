#pragma once
#include <iostream>
#include "TextureManager.h"


class Player
{


private:
	
	int direction;
	float velocity;
	std::shared_ptr<TextureManager> m_playerTexture;
	std::shared_ptr<Sprite2D> playerSprite;

protected:
	struct PlayerPosition {
		float x;
		float y;
	} m_playerPosition;

public:

	Player();

	Player(float _posX, float _posY, float _velocity, std::shared_ptr<TextureManager> _playerTexture);

	virtual ~Player() {
		std::cout << "Player deleted";
	}

	virtual void MoveUp() = 0;

	PlayerPosition GetPlayerPosition();

	void SetPlayerPosition(float _x, float _y);

	float GetPlayerVelocity();

	void SetPlayerVelocity(float _velocity);

	virtual void SetPlayerSprite(int _width, int _height);

	void SetDirectionY(int _direction);

	int GetDirectionY();


	//void Update(float deltaTime);
	
};

