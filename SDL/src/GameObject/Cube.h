#pragma once
#include "Player.h"
class Cube : public Player
{
public:
	Cube();
	Cube(float _posX, float _posY, float _velocity, std::shared_ptr<TextureManager> _playerTexture);
	~Cube();
	void MoveUp() override;
	void MoveUp(const float &_velocity, bool &_isJumping, bool &_isFalling,const float &_jumpBoundY, const float &_deltaTime);
	void SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) override;
	float GetPlayerJumpBoundY(float _jumpHeight);
	

private:

};

