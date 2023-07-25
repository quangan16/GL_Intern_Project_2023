#pragma once
#include "Player.h"

class Ship : public Player
{
public:
	Ship();
	Ship(Vector2 _position, double _rotation, int _direction, double _velocity);
	Ship(Vector2 _position, double _rotation, int _direction, double _velocity, std::shared_ptr<TextureManager> _texture, SDL_RendererFlip _flip, int _width, int _height);
	~Ship();
	void MoveUp(const double& _gravity, const bool& m_onButtonPressed, float _deltaTime) override;
	void ApplyGravity(const double& _gravity, float _deltaTime) override;
	double SyncVelocityToRotationSpeed(float velocity);
	void SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) override;
	std::shared_ptr<Sprite2D> GetPlayerSprite()  override;
	void Rotate(double _rotateSpeed, float _deltaTime) override;
	void FixRotationOnGround(const float& _deltaTime) override;
	const std::shared_ptr<BoxCollider2D> GetCollider() const override;
	void OnGround() override;


};

