#include "Player.h"

Player::Player() : m_playerPosition{ 0.0f, 0.0f }, velocity{ 10.0f } {};



Player::Player(float _posX, float _posY, float _velocity, std::shared_ptr<TextureManager> _playerTexture) : m_playerPosition{ _posX, _posY }, velocity{ _velocity }, m_playerTexture{ _playerTexture } {};

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
	return this->velocity;
}

void Player::SetPlayerVelocity(float _velocity) {
	this->velocity = _velocity;
}

 void Player::SetPlayerSprite(const int &_width,const int &_height,const std::shared_ptr<Sprite2D> &_playerSprite) {
	this->playerSprite = _playerSprite; 
	playerSprite->Set2DPosition(m_playerPosition.x, m_playerPosition.y);
	playerSprite->SetSize(_width, _height);
}

 void Player::SetDirectionY(int _direction) {
	 this->direction = _direction;
 }

 int Player :: GetDirectionY() {
	 return this->direction;
 }

 void Player::UpdatePlayerSpritePos(const std::shared_ptr<Sprite2D>& _playerSprite) {
	
	 _playerSprite->Set2DPosition(m_playerPosition.x, m_playerPosition.y);

 }

 void Player::UpdatePlayerSpriteRotation(const std::shared_ptr<Sprite2D>& _playerSprite) {
 };



