#include "Cube.h"

Cube::Cube(Vector2 _position, double _rotation, int _direction, double _velocity, std::shared_ptr<TextureManager> _playerTexture)
	: Player(_position, _rotation, _direction, _velocity, _playerTexture) {};
	
Cube::~Cube() {
	std::cout << "Cube object deleted";
}

void Cube::Rotate(double _rotateSpeed, float _deltaTime) {
	//std::cout << m_playerRotation << std::endl;
	if (m_playerRotation >= 360.0) {
		m_playerRotation /= 360;
	}
	m_playerRotation += _rotateSpeed * _deltaTime;

}


void Cube::MoveUp(const double& _jumpForce, const double& _gravity, bool& _isJumping, bool& _isFalling, bool& _isOnGround, bool& _jumpBuffer, float _deltaTime) {


	if (_isJumping == true) {
		//std::cout << m_velocity<<std::endl;
		this->SetDirectionY(-1);
		_isOnGround = false;
		Rotate(235.0, _deltaTime);
		m_velocity -= _gravity * _deltaTime;

		//Player falling Down
		if (this->GetPlayerVelocity() <= 0.0f) {
			_isFalling = true;
			//this->SetPlayerVelocity(_gravity);
			/*m_playerPosition.y += m_direction * m_velocity * _deltaTime;*/
			//std::cout << "Down";

		}



		
			if (m_playerPosition.y > 701.0f && _isFalling == true) {
				_isOnGround = true;
				if (_isOnGround == true) {
					m_velocity = 0.0f;
				}
				_isJumping = false;
				_isFalling = false;


			}
		

		
		

	}
	if (_isOnGround == true && _jumpBuffer == 1) {
		_isJumping = true;
		m_velocity = _jumpForce;
		m_velocity -= _gravity * _deltaTime;
		_jumpBuffer = 0;
	}





}






void Cube::ApplyGravity(const double& _gravity, bool& _isJumping, bool& _isFalling, bool& _isOnGround, float _deltaTime) {
	if (_isOnGround == false && _isJumping == false) {
		_isFalling == true;
		m_velocity += _gravity * _deltaTime;
	}

}


void Cube::SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) {
	this->m_playerSprite = _playerSprite;
	_playerSprite->Set2DPosition(m_playerPosition.x, m_playerPosition.y);
	_playerSprite->SetSize(_width, _height);
	_playerSprite->SetRotation(m_playerRotation);
}

float Cube::GetPlayerJumpBoundY(float _jumpHeight) {
	//std::cout << m_playerPosition.y - _jumpHeight << std::endl;
	return m_playerPosition.y - _jumpHeight;
}

void Cube::FixRotationOnGround(const bool& _isOnGround, const float & _deltaTime) {

	if (_isOnGround == true) {
		if (m_playerRotation > 0.0 && m_playerRotation < 45.0) {
			m_playerRotation = 0.0;
		}
		else if ( m_playerRotation > 315.0 && m_playerRotation < 360){
			m_playerRotation = 360;
		}
		else if (m_playerRotation > 225.0 && m_playerRotation < 315.0) m_playerRotation = 270.0;
		else if (m_playerRotation > 135.0 && m_playerRotation < 225)m_playerRotation = 180.0;
		else if (m_playerRotation > 45 && m_playerRotation < 135)m_playerRotation = 90.0;
	}
}

const std::shared_ptr<BoxCollider2D> Cube::GetCollider() const {
	return m_playerCollider;
}

void Cube::OnGround(bool &_isJumping, bool &_isFalling, bool &_isOnGround) {
	if (m_playerPosition.y >701.0f  && _isFalling == true) {
		_isOnGround = true;
		if (_isOnGround == true) {
			m_velocity = 0.0f;
		}
		_isJumping = false;
		_isFalling = false;
		

	}
}

//void Cube::OnCollisionStay(std::shared_ptr<BoxCollider2D> otherCollider) {
//
//}

