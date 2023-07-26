#include "Ship.h"

Ship::Ship() {
	m_playerForm = SHIP;
	m_isJumping = false;
	m_isFalling = true;
	m_isOnGround = false;
	m_isAlive = true;
	m_jumpForce = 3000.0;
	m_playerSpeed = 1100;
}

Ship::Ship(Vector2 _position, double _rotation, int _direction, double _velocity)
	: Player(_position, _rotation, _direction, _velocity)
{
	m_playerForm = SHIP;
	m_isJumping = false;
	m_isFalling = true;
	m_isOnGround = false;
	m_isAlive = true;
	m_jumpForce = 3000.0;
	m_playerSpeed = 1100;

};

Ship::Ship(Vector2 _position, double _rotation, int _direction, double _velocity, std::shared_ptr<TextureManager> _texture, SDL_RendererFlip _flip, int _width, int _height)
	: Player(_position, _rotation, _direction, _velocity)
{
	m_playerForm = SHIP;
	m_isJumping = false;
	m_isFalling = true;
	m_isOnGround = false;
	m_isAlive = true;
	m_jumpForce = 3000.0;
	m_playerSpeed = 1100;
	m_playerSprite = std::make_shared<Sprite2D>(_texture, _flip, _width, _height);

}

Ship::~Ship() {
	std::cout << "Ship object deleted" << std::endl;
}

void Ship::Rotate(double _rotateSpeed, float _deltaTime) {
	
	if (m_isFalling && m_playerRotation < 35) {
		m_playerRotation += _rotateSpeed * 1 / (m_jumpForce /3000 ) * _deltaTime;
	}
	else if (!m_isFalling && m_playerRotation > -35) {
		m_playerRotation -= _rotateSpeed *1/ (m_jumpForce/3000 ) * _deltaTime;
	}
	
	//std::cout << m_playerRotation << std::endl;
	


}

double Ship::SyncVelocityToRotationSpeed(float velocity) {
	// Adjust these parameters based on your game's requirements and testing.
	float minVelocity = 0.0f;
	float maxVelocity = 100.0f;
	double minRotationSpeed = 20.0;
	double maxRotationSpeed = 60.0;

	// Linearly map the velocity to the rotation speed.
	double mappedRotationSpeed = minRotationSpeed + (velocity - minVelocity) * (maxRotationSpeed - minRotationSpeed) / (maxVelocity - minVelocity);

	return mappedRotationSpeed;
}


void Ship::MoveUp(const double& _gravity, const bool& m_onButtonPressed, float _deltaTime) {
	
	if (OnButtonPressed == true) {
		
		m_isJumping = true;
		this -> m_isFalling = false;
		//if(m_jumpForce <= 10000)
		if (m_jumpForce < 5000.0)
		{
			m_jumpForce += 5000.0 * _deltaTime;
		}
		
	}
	else {
		if (m_jumpForce >3000)
		{
			m_jumpForce -= 1000.0 * _deltaTime;
		}
		this -> m_isFalling = true;
		
	}
	//std::cout << m_jumpForce <<std::endl;
	if (m_isJumping == true) {
		if (m_isFalling == false) {
			m_isOnGround = false;
			//if(m_velocity >= -800)
			m_velocity -= m_jumpForce *_deltaTime;
			/*else if (m_velocity < -800) {
				m_velocity -= m_jumpForce  * _deltaTime;
			}*/
			
			
		}
		else {

			
			
			
		}
	}
		//std::cout << m_velocity<<std::endl;
		//OnButtonPressed = true;
		
		
		//std::cout << OnButtonPressed << std::endl;
		
		/*if(m_onButtonPressed == false)
		{
			
		}*/
		
		//Player falling Down
		//if (this->GetPlayerVelocity() < 0.0f) {
		//	m_isFalling = true;
		//	//this->SetPlayerVelocity(_gravity);
		//	/*m_playerPosition.y += m_direction * m_velocity * _deltaTime;*/
		//	//std::cout << "Down";

		////}

	

	
	/*if (m_isOnGround == true && m_jumpBuffer == true) {
		m_isJumping = true;
		m_direction = -1;
		m_velocity = m_jumpForce;
		m_velocity -= _gravity * _deltaTime;
		m_jumpBuffer = false;
	}*/

	
}




void Ship::ApplyGravity(const double& _gravity, float _deltaTime) {
	if (!OnButtonPressed && m_velocity <1300) {
		m_velocity += _gravity * 2/3  * _deltaTime;
	}
		
	

}


void Ship::SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) {
	this->m_playerSprite = _playerSprite;
	_playerSprite->Set2DPosition(m_playerPosition.x, m_playerPosition.y);
	_playerSprite->SetSize(_width, _height);
	_playerSprite->SetRotation(m_playerRotation);
}



void Ship::FixRotationOnGround(const float& _deltaTime) {

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

const std::shared_ptr<BoxCollider2D> Ship::GetCollider() const {
	return this->m_playerCollider;
}

void Ship::OnGround() {
	if (m_isOnGround == true && OnButtonPressed == false) {

		//this->SetDirectionY(-1);
 		m_isJumping = false;
		m_velocity = 0.0;
		m_isFalling = false;
		//FixCollisionOverlaps();
	}



}



std::shared_ptr<Sprite2D> Ship::GetPlayerSprite() {
	return m_playerSprite;

}

