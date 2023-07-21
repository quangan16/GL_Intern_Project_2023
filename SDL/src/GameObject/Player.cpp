#include "Player.h"
#include "ResourceManagers.h"
#include "Collider2D.h"
#include "GameStateBase.h"
#include "Cube.h"
#include "Ship.h"
#include "Wave.h"

Player::Player() : m_playerPosition{ 0.0f, 0.0f }, m_velocity{ 10.0f } {};



Player::Player(Vector2 _position, double _rotation, int _direction, double _velocity, std::shared_ptr<TextureManager> _playerTexture)
	: m_playerPosition{ _position }, m_playerRotation{ _rotation }, m_direction{ _direction }, m_velocity{ _velocity }, m_playerTexture{ _playerTexture },
	m_playerCollider(std::make_shared<BoxCollider2D>(ColliderType::PLAYER, _position, true, 128.0f, 128.0f, ResourceManagers::GetInstance()->GetTexture("collider_border.tga"), SDL_FLIP_NONE)) {}

Player::~Player() {
	std::cout << "Player deleted"<<std::endl;
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

void Player::SetPlayerSprite(const int& _width, const int& _height, const std::shared_ptr<Sprite2D>& _playerSprite) {
	this->m_playerSprite = _playerSprite;
	_playerSprite->Set2DPosition(m_playerPosition.x, m_playerPosition.y);
	_playerSprite->SetSize(_width, _height);


}

void Player::SetDirectionY(int _direction) {
	this->m_direction = _direction;
}

int Player::GetDirectionY() {
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
		 m_playerRotation = 0.0;
		 m_playerPosition.x += 400 * _deltaTime;
	 }

}


void Player::UpdatePlayerPos(float& _deltaTime) {
	//CheckToMap(map_data, _deltaTime);
	// //m_playerPosition.x += m_playerSpeed * _deltaTime;
	m_playerPosition.y += m_direction * m_velocity * _deltaTime;
	
}

 void Player::UpdatePlayerColliderState() {
	 m_playerCollider->SetColliderPosition(m_playerPosition);
 }

 bool Player::OnCollisionStay(std::shared_ptr<BoxCollider2D> _otherCollider,  std::shared_ptr<Player>& _player, std::shared_ptr<Sprite2D>& _playerSprite) {
	 bool isOnGround = false;
	 bool isChangedForm = false;
	 if (m_playerCollider->CheckCollision(_otherCollider)) {
		 if (_otherCollider->GetColliderID() == ColliderType::GROUND) {
			 //Handle side collide with grounds
			 if (m_playerCollider->GetColliderPosition().x + m_playerCollider->GetWidth() >= _otherCollider->GetColliderPosition().x
			 && m_playerCollider->GetColliderPosition().y + m_playerCollider->GetHeight() *7/10 > _otherCollider->GetColliderPosition().y
			 && m_playerCollider->GetColliderPosition().x + m_playerCollider->GetWidth()*(3/4) < _otherCollider->GetColliderPosition().x
			 ) {
				 
				 m_isAlive = false;
			 }
			 //Handle top collide with grounds
			 else if (m_playerCollider->GetColliderPosition().y + m_playerCollider->GetHeight() >= _otherCollider->GetColliderPosition().y 
				 && m_playerCollider->GetColliderPosition().y  < _otherCollider->GetColliderPosition().y) {
				 isOnGround = true;
				 FixCollisionOverlaps(_otherCollider);
			 }
			 //Handle bottom collide with grounds
			 else if (m_playerCollider->GetColliderPosition().y < _otherCollider->GetColliderPosition().y + _otherCollider->GetHeight()) {
				 m_isAlive = false;
			 }
		 }
		 else if (_otherCollider->GetColliderID() == ColliderType::OBSTACLE)
		 {
				 m_isAlive = false;
			 
		 }
		 else if (_otherCollider->GetColliderID() == ColliderType::PORTAL_SHIP && m_changedState == false) {
			 _player = this->TransformToShip();
			 _playerSprite->SetTexture(ResourceManagers::GetInstance()->GetTexture("player_ship_1.png"));
			 isChangedForm = true;
		 }

		 else if (_otherCollider->GetColliderID() == ColliderType::PORTAL_WAVE) {
			 _player = this->TransformToWave();
			 _playerSprite->SetTexture(ResourceManagers::GetInstance()->GetTexture("player_wave_1.png"));
			 
		 }
		   
	 }

	 /*if (isOnGround) {
		 m_isFalling = false;
	 }
	 else {
		 m_isFalling = true;
	 }*/

	 return isOnGround;
 }

 void Player::OnCollisionStay(std::shared_ptr<CircleCollider2D> _otherCollider, std::shared_ptr<Player>& _player, std::shared_ptr<Sprite2D>& _playerSprite) {
	 if (m_playerCollider->CheckCollision(_otherCollider)) {
		 if (_otherCollider->GetColliderID() == ColliderType::JUMP_BOOST && OnButtonPressed) {
			 m_velocity = 10000.0;
		 }
	 }
 }


 void Player::FixCollisionOverlaps(std::shared_ptr<BoxCollider2D> _otherCollider) {
	 float playerBottomCollider = m_playerCollider->GetColliderPosition().y + m_playerCollider->GetHeight();
	 float groundTopCollider = _otherCollider->GetColliderPosition().y;
	 float bottomPenetration = playerBottomCollider - groundTopCollider;
	 if (playerBottomCollider > groundTopCollider) {
		 //std::cout << bottomPenetration << std::endl;
		 this->SetPlayerPosition(this->GetPlayerPosition().x, this->GetPlayerPosition().y - bottomPenetration);
	 }
 }
 
 void Player::Die() {
	 if (m_isAlive == false) {
		 //GameStateMachine::GetInstance()->PopState();
		 GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		 
	 }
 }

 
 std::shared_ptr<TextureManager> Player::GetPlayerTexture() {
	 return m_playerTexture;
 }

 std::shared_ptr<Cube> Player::TransformToCube() {
	 Vector2 currentPosition = this->m_playerPosition;
	 std::shared_ptr<TextureManager> currentTexture = this->m_playerTexture;
	 delete this;
	 return std::make_shared<Cube>(currentPosition, 0.0, 1, 0.0, currentTexture);
 }

 std::shared_ptr<Ship> Player::TransformToShip() {
	 Vector2 currentPosition = this->m_playerPosition;
 	 std::shared_ptr<TextureManager> currentTexture = ResourceManagers::GetInstance()->GetTexture("ship_26.png");
	 this->SetPlayerSprite(300,300, std::make_shared<Sprite2D>(currentTexture, SDL_FLIP_NONE));
	 return std::make_shared<Ship>(currentPosition, 0.0, 1, 0.0, currentTexture);
 }

 std::shared_ptr<Wave> Player::TransformToWave() {
	 Vector2 currentPosition = this->m_playerPosition;
	 std::shared_ptr<TextureManager> currentTexture = this->m_playerTexture;
	 delete this;
	 return std::make_shared<Wave>(currentPosition, 0.0, 1, 0.0, currentTexture);
 }







