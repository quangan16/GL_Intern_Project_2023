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
	void SetPlayerSprite(int _width,int _height) override;
	float GetPlayerJumpBoundY(const PlayerPosition &_currentPosition);
	

private:

};

