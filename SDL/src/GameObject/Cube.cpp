#include "Cube.h"

Cube::Cube(float _posX, float _posY, double _rotation, float _velocity, std::shared_ptr<TextureManager> _playerTexture) : Player(_posX, _posY,_rotation, _velocity, _playerTexture) {};

Cube::~Cube() {
	std::cout << "Cube object deleted";
}


void Cube::MoveUp(const float &_jumpForce, const float &_gravity, bool &_isJumping, bool &_isFalling, const float &_jumpBoundY, bool& _jumpBuffer, float _deltaTime) {
	
	
	if (_isJumping == true) {
		if (this->GetPlayerPosition().y >= 701.0f) {
			_isJumping = false;
			_isFalling = false;
			
		}
		//Player falling Down
		if (this->GetPlayerPosition().y < _jumpBoundY || _isFalling == true) {
			_isFalling = true;
			this->SetDirectionY(1);
			this->SetPlayerVelocity(_gravity);
			m_playerPosition.y += m_direction * m_velocity * _deltaTime;
			//std::cout << "Down";

		}
		//Player jumping up / moving Up
		else if (this->GetPlayerPosition().y >= _jumpBoundY && _isFalling == false) {
			this->SetDirectionY(-1);
			this->SetPlayerVelocity(_jumpForce);
			m_playerPosition.y += m_direction * m_velocity *_deltaTime;
			//std::cout << "Up";
		}


		
	}
	if (_isJumping == false && _jumpBuffer==1) {
		_isJumping = true;
		_jumpBuffer = 0;
	}
	
	
	
}

void Cube::SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) {
	this->playerSprite = _playerSprite;
	playerSprite->Set2DPosition(m_playerPosition.x, m_playerPosition.y);
	playerSprite->SetSize(_width, _height);
}

float Cube::GetPlayerJumpBoundY(float _jumpHeight) {
	std::cout << m_playerPosition.y - _jumpHeight<<std::endl;
	return m_playerPosition.y - _jumpHeight;
}



