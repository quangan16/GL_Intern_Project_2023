#include "Ball.h"

Ball::Ball() {
	m_playerForm = BALL;
	m_isJumping = false;
	m_isFalling = true;
	m_isOnGround = false;
	m_isAlive = true;
	m_jumpForce = 3000.0;
	m_playerSpeed = 1100;
}

Ball::Ball(Vector2 _position, double _rotation, int _direction, double _velocity)
	: Player(_position, _rotation, _direction, _velocity)
{
	m_playerForm = BALL;
	m_isJumping = false;
	m_isFalling = true;
	m_isOnGround = false;
	m_isAlive = true;
	m_jumpForce = 3000.0;
	m_playerSpeed = 1100;

}
Ball::Ball(Vector2 _position, double _rotation, int _direction, double _velocity, std::shared_ptr<TextureManager> _texture, SDL_RendererFlip _flip, int _width, int _height)
	: Player(_position, _rotation, _direction, _velocity)
{
	m_playerForm = BALL;
	m_isJumping = false;
	m_isFalling = true;
	m_isOnGround = false;
	m_isAlive = true;
	m_jumpForce = 3000.0;
	m_playerSpeed = 1100;
	m_playerSprite = std::make_shared<Sprite2D>(_texture, _flip, _width, _height);

}
;

Ball::~Ball() {
	std::cout << "Ball object deleted" << std::endl;
}

void Ball::Rotate(double _rotateSpeed, float _deltaTime) {




}




void Ball::MoveUp(const double& _gravity, const bool& m_onButtonPressed, float _deltaTime) {

	if (OnButtonDown == true && m_isOnGround) {

		m_isJumping = true;
		this->m_isFalling = false;
		//if(m_jumpForce <= 10000)
		m_jumpForce += 2000 * _deltaTime;
	}
	else {


		this->m_isFalling = true;
	}
	//std::cout << m_jumpForce <<std::endl;
	if (m_isJumping == true) {
		if (m_isFalling == false) {
			m_isOnGround = false;
			m_direction = -m_direction;


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




void Ball::ApplyGravity(const double& _gravity, float _deltaTime) {
	if (!OnButtonPressed && m_velocity < 1300) {
		m_velocity += _gravity * 2 / 3 * _deltaTime;
	}



}


void Ball::SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) {
	this->m_playerSprite = _playerSprite;
	_playerSprite->Set2DPosition(m_playerPosition.x, m_playerPosition.y);
	_playerSprite->SetSize(_width, _height);
	_playerSprite->SetRotation(m_playerRotation);
}



void Ball::FixRotationOnGround(const float& _deltaTime) {

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

const std::shared_ptr<BoxCollider2D> Ball::GetCollider() const {
	return this->m_playerCollider;
}

void Ball::OnGround() {
	if (m_isOnGround == true && OnButtonPressed == false) {

		//this->SetDirectionY(-1);
		m_isJumping = false;
		m_velocity = 0.0;
		m_isFalling = false;
		//FixCollisionOverlaps();
	}



}



std::shared_ptr<Sprite2D> Ball::GetPlayerSprite() {
	return m_playerSprite;

}

