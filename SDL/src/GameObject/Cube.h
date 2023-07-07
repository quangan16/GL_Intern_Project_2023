#pragma once
#include "Player.h"
class Cube : public Player
{
public:
	Cube();
	Cube(float _posX, float _posY, float _velocity, std::shared_ptr<TextureManager> _playerTexture);
	~Cube();
	void MoveUp(const float& _jumpForce, const float &_gravity, bool& _isJumping, bool& _isFalling, const float& _jumpBoundY,  float _deltaTime) override;
	
	void SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) override;
	float GetPlayerJumpBoundY(float _jumpHeight) override;
	

private:

};

