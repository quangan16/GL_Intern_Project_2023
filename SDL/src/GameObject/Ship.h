#pragma once
#include "Player.h"

class Ship : public Player
{
public:
	Ship();
	Ship(Vector2 _position, double _rotation, int _direction, double _velocity, std::shared_ptr<TextureManager> _playerTexture);
	~Ship();
	void MoveUp(const double& _jumpForce, const double& _gravity, bool& _isJumping, bool& _isFalling, bool& _isOnGround, bool& _jumpBuffer, float _deltaTime) override;
	void ApplyGravity(const double& _gravity, bool& _isFalling, bool& _isJumping, bool& _isOnGround, float _deltaTime) override;

	void SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) override;
	void Rotate(double _angle, const bool& _isJumping, const bool& _isFalling, float deltaTime) override;
	void FixRotationOnGround(const bool& _isOnGround, const float& deltaTime) override;
	const std::shared_ptr<BoxCollider2D> GetCollider() const override;
	void OnGround(bool& _isJumping, bool& _isFalling, bool& _jumpBuffer, bool& _isOnGround) override;

	void GravityPull(float _deltaTime);
	void FlyUp(const float& _velocity, const float& _gravity, float _deltaTime);
};

