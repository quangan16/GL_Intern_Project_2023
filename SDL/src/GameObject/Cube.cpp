#include "Cube.h"

Cube::Cube() {
	m_playerForm = CUBE;
	m_isJumping = false;
	m_isFalling = true;
	m_isOnGround = false;
	m_jumpForce = 3000.0;
}

Cube::Cube(Vector2 _position, double _rotation, int _direction, double _velocity, std::shared_ptr<TextureManager> _playerTexture)
	: Player(_position, _rotation, _direction, _velocity, _playerTexture) {
	m_playerForm = CUBE;
	m_isJumping = false;
	m_isFalling = true;
	m_isOnGround = false;
	m_jumpForce = 3000.0;
};

Cube::~Cube() {
	std::cout << "Cube object deleted"<<std::endl;
}

void Cube::Rotate(double _rotateSpeed, float _deltaTime) {

	//std::cout << m_playerRotation << std::endl;
	if (m_isFalling || m_isJumping) {
		if (m_playerRotation >= 360.0) {
			m_playerRotation /= 360;
		}
		m_playerRotation += _rotateSpeed * _deltaTime;
	}
	
	

}


void Cube::MoveUp(const double& _gravity, const bool& m_onButtonPressed, float _deltaTime) {


	if (m_isJumping == true) {
		//std::cout << m_velocity<<std::endl;
		this->SetDirectionY(-1);
		m_isOnGround = false;
		
		m_velocity -= _gravity * _deltaTime;

		//Player falling Down
		if (this->GetPlayerVelocity() < 0.0f) {
			m_isFalling = true;
			//this->SetPlayerVelocity(_gravity);
			/*m_playerPosition.y += m_direction * m_velocity * _deltaTime;*/
			//std::cout << "Down";

		}

	}
	if (m_isOnGround == true && m_jumpBuffer == true) {
		m_isJumping = true;
		m_direction = -1;
		m_velocity = m_jumpForce;
		m_velocity -= _gravity * _deltaTime;
		m_jumpBuffer = 0;
	}


}




void Cube::ApplyGravity(const double& _gravity, float _deltaTime) {
	if (m_isOnGround == false && m_isJumping == false) {
		m_isFalling == true;
		m_velocity += _gravity * _deltaTime;
	}

}


void Cube::SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) {
	this->m_playerSprite = _playerSprite;
	_playerSprite->Set2DPosition(m_playerPosition.x, m_playerPosition.y);
	_playerSprite->SetSize(_width, _height);
	_playerSprite->SetRotation(m_playerRotation);
}

std::shared_ptr<Sprite2D> Cube::GetPlayerSprite() {
	return m_playerSprite;
	
}


void Cube::FixRotationOnGround(const float& _deltaTime) {

	if (m_isOnGround == true) {
		if (m_playerRotation > 0.0 && m_playerRotation < 45.0) {
			m_playerRotation = 0.0;
		}
		else if (m_playerRotation > 315.0 && m_playerRotation < 360) {
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

void Cube::OnGround() {
	if (m_isOnGround == true) {



		this->SetDirectionY(1);
		m_isJumping = false;
		m_velocity = 0.0f;
		m_isFalling = false;
		//FixCollisionOverlaps();
	}
	
	
	
}



