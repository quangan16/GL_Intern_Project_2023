#pragma once
#include "Player.h"

class Spider : public Player
{
public:
	Spider();
	Spider(Vector2 _position, double _rotation, int _direction, double _velocity);
	Spider(Vector2 _position, double _rotation, int _direction, double _velocity, std::shared_ptr<TextureManager> _playerTexture, int width, int height, int spriteRow, int frameCount, int numAction, float  frameTime, bool _repeat);
	~Spider();
	void MoveUp(const double& _gravity, const bool& m_onButtonPressed, float _deltaTime) override;
	void ApplyGravity(const double& _gravity, float _deltaTime) override;
	void SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) override;
	std::shared_ptr<Sprite2D> GetPlayerSprite()  override;
	void Rotate(double _rotateSpeed, float _deltaTime) override;
	void FixRotationOnGround(const float& _deltaTime) override;
	const std::shared_ptr<BoxCollider2D> GetCollider() const override;
	void OnGround() override;


};

