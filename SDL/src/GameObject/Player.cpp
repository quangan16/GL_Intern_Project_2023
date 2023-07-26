#include "Player.h"

#include <chrono>
#include <thread>

#include "ResourceManagers.h"
#include "Collider2D.h"
#include "GameStateBase.h"
#include "Ball.h"
#include "Cube.h"
#include "Ship.h"
#include "Sound.h"
#include "Wave.h"
#include "Spider.h"


Player::Player() : m_playerPosition{ 0.0f, 0.0f }, m_velocity{ 10.0f } {};



Player::Player(Vector2 _position, double _rotation, int _direction, double _velocity)
	: m_playerPosition{ _position }, m_playerRotation{ _rotation }, m_direction{ _direction }, m_velocity{ _velocity },
	m_playerCollider(std::make_shared<BoxCollider2D>(ColliderType::PLAYER, _position, true, TILE_SIZE, TILE_SIZE, ResourceManagers::GetInstance()->GetTexture("collider_border.png"), SDL_FLIP_NONE))
{
	m_isAlive = true;
	m_playerDieEffect = std::make_shared<SpriteAnimation>(ResourceManagers::GetInstance()->GetTexture("Player_Die_1.tga"), TILE_SIZE, TILE_SIZE , 1, 59, 1, 0.01f, false);
	m_playerJumpEffect = std::make_shared<SpriteAnimation>(ResourceManagers::GetInstance()->GetTexture("Player_Jump_Effect_1.tga"), TILE_SIZE, TILE_SIZE, 1, 4, 1, 0.02f, false);
	m_playerTrailEffect = std::make_shared<SpriteAnimation>(ResourceManagers::GetInstance()->GetTexture("Player_Trail_Effect_1.tga"), TILE_SIZE, TILE_SIZE, 1, 9, 1, 0.03f, true);
}



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

const double& Player::GetPlayerRotation()
{
	return m_playerRotation;
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

void Player::UpdatePlayerSprite() {

	m_playerSprite->Set2DPosition(m_playerPosition.x, m_playerPosition.y);
	m_playerSprite->SetRotation(m_playerRotation);

}

void Player::UpdatePlayerAnimation()
{
	m_playerAnimation->Set2DPosition(m_playerPosition.x, m_playerPosition.y);
}




void Player::UpdatePlayerSpriteRotation(const std::shared_ptr<Sprite2D>& _playerSprite) {
};

 void Player::RunIntoScene (const Vector2 &_readyPos, float _deltaTime) {
	 if (m_playerPosition.x >= _readyPos.x)  return;
	 else {
		 m_playerRotation = 0.0;
		 m_playerPosition.x += 7000 * _deltaTime;
	 }

}


void Player::UpdatePlayerPos(float& _deltaTime) {
	//CheckToMap(map_data, _deltaTime);
	if(m_isAlive)
	{
		m_playerPosition.x += m_playerSpeed * _deltaTime;
		m_playerPosition.y += m_direction * m_velocity * _deltaTime;
	}
	 
	
	
}

 void Player::UpdatePlayerColliderState() {
	 m_playerCollider->SetColliderPosition(m_playerPosition);
 }

 bool Player::OnCollisionStay(std::shared_ptr<BoxCollider2D> _otherCollider,  std::shared_ptr<Player>& _player) {
	
	 bool isOnGround = false;
	 bool isChangedForm = false;
	 if (m_playerCollider->CheckCollision(_otherCollider)) {
		 if (_otherCollider->GetColliderID() == ColliderType::GROUND) {
			 //Handle side collide with grounds
			  if (m_playerCollider->GetColliderPosition().x + m_playerCollider->GetWidth() >= _otherCollider->GetColliderPosition().x
				 && m_playerCollider->GetColliderPosition().x + m_playerCollider->GetWidth() * (4 / 5) < _otherCollider->GetColliderPosition().x
				 && m_playerCollider->GetColliderPosition().y + m_playerCollider->GetHeight() * (4 / 10) > _otherCollider->GetColliderPosition().y
				 && m_playerCollider->GetColliderPosition().y + m_playerCollider->GetHeight() < _otherCollider->GetColliderPosition().y + _otherCollider->GetHeight()
				 ) {
				 m_isAlive = false;
			 }
			 
			 //Handle  collide with ground's surface
			 else if (m_playerCollider->GetColliderPosition().y + m_playerCollider->GetHeight() >= _otherCollider->GetColliderPosition().y 
				 && m_playerCollider->GetColliderPosition().y  < _otherCollider->GetColliderPosition().y) {
				 isOnGround = true;
				 FixCollisionOverlapsOnSurface(_otherCollider);
			 }
			 else if (m_playerCollider->GetColliderPosition().y > _otherCollider->GetColliderPosition().y && (m_playerForm == WAVE || m_playerForm == SHIP) && m_playerCollider->GetColliderPosition().y + m_playerCollider->GetHeight() > _otherCollider->GetColliderPosition().y + _otherCollider->GetHeight())
			  {
				  isOnGround = true;
				  FixCollisionOverlapsUnderSurface(_otherCollider);
			  }
			 else if (m_playerCollider->GetColliderPosition().y < _otherCollider->GetColliderPosition().y + _otherCollider->GetHeight()
				) {

				  m_isAlive = false;

			  }
			 
			 //Handle collide with grounds bottom
			 
			  
		 
			 
		 }
		  if (_otherCollider->GetColliderID() == ColliderType::OBSTACLE)
		 {
			 

				 m_isAlive = false;
			 
		 }
		 if (_otherCollider->GetColliderID() == ColliderType::PORTAL_CUBE && m_changedState == false) {
			 _player = this->TransformToCube();
			 Camera::GetInstance()->SetTarget(_player);
			 _player->m_playerCollider->SetColliderSize(TILE_SIZE, TILE_SIZE);
			 _player->m_playerSprite->SetTexture(ResourceManagers::GetInstance()->GetTexture("player_cube_" + std::to_string(m_iCharacterTexture_index) + ".tga"));
			 _player->m_playerSprite->SetSize(TILE_SIZE , TILE_SIZE );
			 m_changedState = true;
		 }

		 if (_otherCollider->GetColliderID() == ColliderType::PORTAL_SHIP && m_changedState == false) {
			 _player = this->TransformToShip();
			 Camera::GetInstance()->SetTarget(_player);
			 _player->m_playerCollider->SetColliderSize(TILE_SIZE * 5 / 4, TILE_SIZE * 2 / 3);
			 _player->m_playerSprite->SetTexture(ResourceManagers::GetInstance()->GetTexture("player_ship_" + std::to_string(m_iCharacterTexture_index) + ".tga"));
			 _player->m_playerSprite->SetSize(TILE_SIZE * 5/4 , TILE_SIZE*2/3);
			 m_changedState = true;
		 }

		 if (_otherCollider->GetColliderID() == ColliderType::PORTAL_WAVE) {
			 _player = this->TransformToWave();
			 Camera::GetInstance()->SetTarget(_player);
			 _player->m_playerCollider->SetColliderSize(TILE_SIZE, TILE_SIZE * 2 / 3);
			 _player->m_playerSprite->SetTexture(ResourceManagers::GetInstance()->GetTexture("player_wave_" + std::to_string(m_iCharacterTexture_index) + ".tga"));
			 
			 _player->m_playerSprite->SetSize(TILE_SIZE , TILE_SIZE * 2 / 3);

			 m_changedState = true;
		 }
		 if (_otherCollider->GetColliderID() == ColliderType::PORTAL_BALL) {
			 _player = this->TransformToBall();
			 Camera::GetInstance()->SetTarget(_player);
			 _player->m_playerCollider->SetColliderSize(TILE_SIZE, TILE_SIZE );
			 _player->m_playerSprite->SetTexture(ResourceManagers::GetInstance()->GetTexture("player_bug_1.tga"));

			 _player->m_playerSprite->SetSize(TILE_SIZE, TILE_SIZE );

			 m_changedState = true;
		 }
		 if (_otherCollider->GetColliderID() == ColliderType::PORTAL_SPIDER && m_changedState == false) {
			 
			 _player = this->TransformToSpider();
			 Camera::GetInstance()->SetTarget(_player);
			 _player->m_playerCollider->SetColliderSize(TILE_SIZE, TILE_SIZE);
			 /*_playerSprite->SetTexture(ResourceManagers::GetInstance()->GetTexture("player_spider_1.tga"));

			 _playerSprite->SetSize(TILE_SIZE, TILE_SIZE);*/

			 m_changedState = true;
		 }
		 if (m_changedState == true) {
			 m_changedState = false;
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

 void Player::OnCollisionTrigger(std::shared_ptr<CircleCollider2D> _otherCollider, double& _gravity,const float& _deltaTime) {
	 if (m_playerCollider->CheckCollision(_otherCollider)) {
		
		 if (_otherCollider->GetColliderID() == ColliderType::JUMP_BOOST && m_playerForm == CUBE && OnButtonDown == true) {
			 //std::cout << "ok" << std::endl;
			 //std::cout << "contact";

			 m_isJumping = false;
			 m_isJumping = true;
			 m_velocity = m_jumpForce;
			 m_jumpBuffer = false;
			 
		 }
		 if (_otherCollider->GetColliderID() == ColliderType::JUMP_BOOST_AUTO && m_playerForm == CUBE) {
			 //std::cout << "ok" << std::endl;
			 m_isJumping = false;
			 m_isJumping = true;
			 m_velocity = m_jumpForce * 1.5;
			 m_jumpBuffer = false;

		 }
	 }
 }




 void Player::FixCollisionOverlapsOnSurface(std::shared_ptr<BoxCollider2D> _otherCollider) {
	 float playerBottomCollider = m_playerCollider->GetColliderPosition().y + m_playerCollider->GetHeight();
	 float groundTopCollider = _otherCollider->GetColliderPosition().y;
	 float bottomPenetration = std::abs(playerBottomCollider - groundTopCollider);
	 if (playerBottomCollider > groundTopCollider) {
		 //std::cout << bottomPenetration << std::endl;
		 
		 this->SetPlayerPosition(this->GetPlayerPosition().x, this->GetPlayerPosition().y - bottomPenetration);
	 }
 }

 void Player::FixCollisionOverlapsUnderSurface(std::shared_ptr<BoxCollider2D> _otherCollider) {
	 float playerTopCollider = m_playerCollider->GetColliderPosition().y;
	 float groundBottomCollider = _otherCollider->GetColliderPosition().y + _otherCollider->GetHeight();
	 float topPenetration = std::abs(playerTopCollider - groundBottomCollider);
	 if (playerTopCollider < groundBottomCollider) {
		

		 this->SetPlayerPosition(this->GetPlayerPosition().x, this->GetPlayerPosition().y + topPenetration);
	 }
 }

 
 void Player::Die(std::shared_ptr<Background> &_bg,std::shared_ptr<Sound>& _bgSound, std::shared_ptr<Sound>& _DieSfx,float &_dieTime, float waitTime) {
 	
	
	 if (m_isAlive == false) {
		 //GameStateMachine::GetInstance()->PopState();
		 if(isMuted) _bgSound->StopSound();
		 if (!isMuted)_DieSfx->PlaySoundOnce();
		 _bg->SetSpeed(0.0f);
		 
		 
		 //std::cout << _dieTime;
		 if(timer >= _dieTime + 2.0f)
		 {
			 GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		 }
		
		 
	 }
 }

 
 std::shared_ptr<TextureManager> Player::GetPlayerTexture() {
	 return m_playerTexture;
 }

 std::shared_ptr<Cube> Player::TransformToCube() {
	 Vector2 currentPosition = this->m_playerPosition;
	 std::shared_ptr<TextureManager> currentTexture = this->m_playerTexture;
	 return std::make_shared<Cube>(currentPosition, 0.0, 1, 0.0, currentTexture,SDL_FLIP_NONE, TILE_SIZE,TILE_SIZE);
 }

 std::shared_ptr<Ship> Player::TransformToShip() {
	 Vector2 currentPosition = this->m_playerPosition;
 	 std::shared_ptr<TextureManager> currentTexture = ResourceManagers::GetInstance()->GetTexture("player_ship_1.tga");

	 //this->SetPlayerSprite(300, 00, std::make_shared<Sprite2D>(currentTexture, SDL_FLIP_NONE));
	 
	 return std::make_shared<Ship>(currentPosition, 0.0, 1, 0.0, currentTexture, SDL_FLIP_NONE, TILE_SIZE, TILE_SIZE);
	 
 }

 std::shared_ptr<Wave> Player::TransformToWave() {
	 Vector2 currentPosition = this->m_playerPosition;
	 std::shared_ptr<TextureManager> currentTexture = this->m_playerTexture;
	 return std::make_shared<Wave>(currentPosition, 0.0, 1, 0.0, currentTexture, SDL_FLIP_NONE, TILE_SIZE, TILE_SIZE);
 }

 std::shared_ptr<Ball> Player::TransformToBall() {
	 Vector2 currentPosition = this->m_playerPosition;
	 std::shared_ptr<TextureManager> currentTexture = this->m_playerTexture;
	 return std::make_shared<Ball>(currentPosition, 0.0, 1, 0.0, currentTexture, SDL_FLIP_NONE, TILE_SIZE, TILE_SIZE);
 }

 std::shared_ptr<Spider> Player::TransformToSpider() {
	 Vector2 currentPosition = this->m_playerPosition;
	 this->m_playerSprite = nullptr;
	 std::shared_ptr<TextureManager> currentTexture = ResourceManagers::GetInstance()->GetTexture("player_spider_1.tga");
	 return std::make_shared<Spider>(currentPosition, 0.0, 1, 0.0, ResourceManagers::GetInstance()->GetTexture("player_spider_1.tga"),  TILE_SIZE, TILE_SIZE,  1,  16,  1,   0.01,  true);
 }


 std::shared_ptr<SpriteAnimation> Player::GetPlayerAnimation()
 {
	 return this->m_playerAnimation;
 }



