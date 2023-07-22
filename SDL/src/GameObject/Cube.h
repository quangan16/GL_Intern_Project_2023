#pragma once
#include "Player.h"
#include <memory>
class Cube : public Player
{
public:
	Cube();
	Cube(Vector2 _position, double _rotation,int _direction, double _velocity, std::shared_ptr<TextureManager> _playerTexture);
	~Cube();
	void MoveUp(const double &_gravity, const bool& m_onButtonPressed,  float _deltaTime) override;
	void ApplyGravity(const double& _gravity, float _deltaTime) override;
	
	void SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) override;
	std::shared_ptr<Sprite2D> GetPlayerSprite();
	void Rotate(double _angle, float deltaTime) override;
	void FixRotationOnGround(const float &deltaTime) override;
	const std::shared_ptr<BoxCollider2D> GetCollider() const override;
	void OnGround() override;

protected:
	

};

