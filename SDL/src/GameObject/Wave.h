#pragma once
#include "Player.h"
#include "Define.h"
#include <memory>
class Wave : public Player
{
public:
	Wave();
	Wave(Vector2 _position, double _rotation, int _direction, double _velocity);
	Wave(Vector2 _position, double _rotation, int _direction, double _velocity, std::shared_ptr<TextureManager> _texture, SDL_RendererFlip _flip, int _width, int _height);
	~Wave();
	void MoveUp(const double& _gravity, const bool& m_onButtonPressed, float _deltaTime) override;
	void ApplyGravity(const double& _gravity, float _deltaTime) override;

	void SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) override;
	std::shared_ptr<Sprite2D> GetPlayerSprite() override;
	void Rotate(double _rotateSpeed, float _deltaTime) override;
	void FixRotationOnGround(const float& _deltaTime) override;
	const std::shared_ptr<BoxCollider2D> GetCollider() const override;
	
	void OnGround() override;

protected:


};

