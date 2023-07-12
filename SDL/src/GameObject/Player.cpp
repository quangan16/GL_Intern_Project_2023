#include "Player.h"

Player::Player() : m_playerPosition{ 0.0f, 0.0f }, m_velocity{ 10.0f } {};



Player::Player(float _posX, float _posY, double _rotation, int _direction, double _velocity, std::shared_ptr<TextureManager> _playerTexture)
: m_playerPosition{ _posX, _posY }, m_playerRotation{ _rotation }, m_direction{_direction}, m_velocity{_velocity}, m_playerTexture{_playerTexture} {};

Player::~Player() {
	std::cout << "Player deleted";
}


Vector2 Player::GetPlayerPosition() {
	return m_playerPosition;
}

void Player::SetPlayerPosition(float _x, float _y) {
	m_playerPosition.x = _x;
	m_playerPosition.y = _y;
}

float Player::GetPlayerVelocity() {
	return this->m_velocity;
}

void Player::SetPlayerVelocity(float _velocity) {
	this->m_velocity = _velocity;
}

 void Player::SetPlayerSprite(const int &_width,const int &_height,const std::shared_ptr<Sprite2D> &_playerSprite) {
	this->m_playerSprite = _playerSprite; 
	_playerSprite->Set2DPosition(m_playerPosition.x, m_playerPosition.y);
	_playerSprite->SetSize(_width, _height);
	
	
}

 void Player::SetDirectionY(int _direction) {
	 this->m_direction = _direction;
 }

 int Player :: GetDirectionY() {
	 return this->m_direction;
 }

 void Player::UpdatePlayerSprite(const std::shared_ptr<Sprite2D>& _playerSprite) {
	
	 _playerSprite->Set2DPosition(m_playerPosition.x, m_playerPosition.y);
	 _playerSprite->SetRotation(m_playerRotation);

 }



 void Player::UpdatePlayerSpriteRotation(const std::shared_ptr<Sprite2D>& _playerSprite) {
 };

 void Player::RunIntoScene (const Vector2 &_readyPos, float _deltaTime) {
	 if (m_playerPosition.x >= _readyPos.x)  return;
	 else {
		 m_playerPosition.y = 700.0f;
		 m_playerRotation = 0.0;
		 m_velocity = 0.0f;
		 m_playerPosition.x += 400 * _deltaTime;
	 }

 }

 float Player::GetPlayerJumpBoundY(float _jumpHeight) {
	 float jumpYBound = 0.0f;
	 return jumpYBound;
 }

 void Player::UpdatePlayerPos(float& _deltaTime) {
	 m_playerPosition.y += m_direction * m_velocity * _deltaTime;
 }




