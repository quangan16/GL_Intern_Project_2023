#pragma once
#include "Player.h"
class Cube : public Player
{
public:
	Cube();
	Cube(float _posX, float _posY, double _rotation,int _direction, float _velocity, std::shared_ptr<TextureManager> _playerTexture);
	~Cube();
	void MoveUp(const float& _jumpForce, const float &_gravity, bool &_isJumping,bool& _isFalling,bool &_isOnGround, const float& _jumpBoundY, bool &_jumpBuffer,  float _deltaTime) override;
	void ApplyGravity(const float& _gravity, bool& _isFalling, bool& _isJumping, bool& _isOnGround, float _deltaTime) override;
	
	void SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) override;
	float GetPlayerJumpBoundY(float _jumpHeight) override;
	void Rotate(double _angle, float deltaTime) override;
	void FixRotationOnGround(const bool& _isOnGround, double& _playerRotation);
private:

};

