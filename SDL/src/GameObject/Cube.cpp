#include "Cube.h"

Cube::Cube(float _posX, float _posY, float _velocity, std::shared_ptr<TextureManager> _playerTexture) : Player(_posX, _posY, _velocity, _playerTexture) {};

Cube::~Cube() {
	std::cout << "Cube object deleted";
}


void Cube::MoveUp(const float &_jumpForce, const float &_gravity, bool &_isJumping, bool &_isFalling, const float &_jumpBoundY, float _deltaTime) {
	
	
	if (_isJumping == true) {
		if (this->GetPlayerPosition().y >= _jumpBoundY) {
			this->SetDirectionY(-1);
			this->SetPlayerVelocity(_jumpForce);
			m_playerPosition.y += m_direction * m_velocity;
			std::cout << "Yes";
		}


		else if (this->GetPlayerPosition().y < _jumpBoundY) {
			this->SetDirectionY(1);
			this->SetPlayerVelocity(_gravity);
			m_playerPosition.y += m_direction * m_velocity;
			std::cout << "No";

		}
		else if (this->GetPlayerPosition().y <= 700.0f) {
			_isJumping == false;
		}
	}
	else {

	}
	
	
}

void Cube::SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) {
	this->playerSprite = _playerSprite;
	playerSprite->Set2DPosition(m_playerPosition.x, m_playerPosition.y);
	playerSprite->SetSize(_width, _height);
}

float Cube::GetPlayerJumpBoundY(float _jumpHeight) {
	std::cout << m_playerPosition.y - _jumpHeight;
	return m_playerPosition.y - _jumpHeight;
}



