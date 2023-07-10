#include "Cube.h"

Cube::Cube(float _posX, float _posY, double _rotation, int _direction, float _velocity, std::shared_ptr<TextureManager> _playerTexture) 
	: Player(_posX, _posY,_rotation, _direction, _velocity,  _playerTexture) {};

Cube::~Cube() {
	std::cout << "Cube object deleted";
}

void Cube::Rotate(double _angle, float _deltaTime) {
	//std::cout << m_playerRotation << std::endl;
	if (m_playerRotation >= 360.0) {
		m_playerRotation /= 360;
	}
	m_playerRotation += _angle * _deltaTime;

}


void Cube::MoveUp(const float &_jumpForce, const float &_gravity, bool &_isJumping, bool &_isFalling,bool &_isOnGround, const float &_jumpBoundY, bool& _jumpBuffer, float _deltaTime) {
	
	
	if (_isJumping == true) {
		this->SetDirectionY(-1);
		_isOnGround = false;
		Rotate(180.0, _deltaTime);
		m_velocity -= _gravity * _deltaTime;
		
		//Player falling Down
		if (this->GetPlayerVelocity() <=0.0f ) {
			_isFalling = true;
			//this->SetPlayerVelocity(_gravity);
			/*m_playerPosition.y += m_direction * m_velocity * _deltaTime;*/
			std::cout << "Down";

		}
		
		
		
		
	}
	if (_isJumping == false && _jumpBuffer == 1) {
		_isJumping = true;
		m_velocity = 1000.0f;
		m_velocity -= _gravity * _deltaTime;
		_jumpBuffer = 0;
	}
	
	
	
	
}






void Cube::ApplyGravity(const float& _gravity, bool& _isJumping, bool& _isFalling, bool& _isOnGround, float _deltaTime) {
	
	
	
	
	if (this->GetPlayerPosition().y > 700.0f && _isFalling == true) {
			;
		if (_isOnGround == false) {
			m_velocity = 0.0f;
		}
		_isJumping = false;
		_isFalling = false;
		_isOnGround = true;

	}
	
	
	
}


void Cube::SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) {
	this->m_playerSprite = _playerSprite;
	_playerSprite->Set2DPosition(m_playerPosition.x, m_playerPosition.y);
	_playerSprite->SetSize(_width, _height);
	_playerSprite->SetRotation(m_playerRotation);

}

float Cube::GetPlayerJumpBoundY(float _jumpHeight) {
	std::cout << m_playerPosition.y - _jumpHeight<<std::endl;
	return m_playerPosition.y - _jumpHeight;
}

//void Cube::FixRotationOnGround(const bool &_isOnGround){
//
//	if (_isOnGround == true) {
//		if(m_playerRotation >= )
//	}
//}



