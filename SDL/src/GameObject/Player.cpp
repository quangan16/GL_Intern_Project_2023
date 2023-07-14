#include "Player.h"
#include "ResourceManagers.h"
#include "Collider2D.h"

Player::Player() : m_playerPosition{ 0.0f, 0.0f }, m_velocity{ 10.0f } {};



Player::Player(Vector2 _position, double _rotation, int _direction, double _velocity, std::shared_ptr<TextureManager> _playerTexture)
	: m_playerPosition{ _position }, m_playerRotation{ _rotation }, m_direction{ _direction }, m_velocity{ _velocity }, m_playerTexture{ _playerTexture }, m_playerCollider(std::make_shared<BoxCollider2D>(ColliderType::Player, _position, true, 80.0f, 80.0f, ResourceManagers::GetInstance()->GetTexture("collider_border.tga"), SDL_FLIP_NONE)) {}

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
		 m_playerRotation = 0;
		 m_playerPosition.x += 400 * _deltaTime;
	 }

}



 void Player::UpdatePlayerPos(float& _deltaTime) {
	 m_playerPosition.y += m_direction * m_velocity * _deltaTime;
 }

 void Player::UpdatePlayerColliderState() {
	 m_playerCollider->SetColliderPosition(m_playerPosition);
 }

 void Player::OnCollisionStay(std::shared_ptr<BoxCollider2D> otherCollider, bool &_isOnGround, bool &_isFalling) {
	 if (m_playerCollider->CheckCollision(otherCollider)) {
		 if (otherCollider->GetColliderID() == ColliderType::GROUND) {
			 _isOnGround = true;
		 }
	 }
 }
 

void Player::CheckToMap(Map& map_data)
{
	//Check vertical
	int width_min = TILE_SIZE;
	int height_min = TILE_SIZE;

	int i_leftBound = (m_playerPosition.x) / TILE_SIZE;
	int i_rightBound = (m_playerPosition.x + width_min) / TILE_SIZE;


	int i_topBound = (m_playerPosition.y + m_velocity) / TILE_SIZE;
	int i_bottomBound = (m_playerPosition.y + height_min + m_velocity - 1) / TILE_SIZE;

	if (i_leftBound >= 0 && i_rightBound < MAX_MAP_X && i_topBound >= 0 && i_bottomBound < MAX_MAP_Y)
	{
		//if (m_velocity > 0)
		//{
			if (map_data.tile[i_bottomBound][i_leftBound] != 0
				|| map_data.tile[i_bottomBound][i_rightBound] != 0)
			{
				m_playerPosition.y = i_bottomBound * TILE_SIZE;
				m_playerPosition.y -= (height_min + 1);
				m_velocity = 0;
			}
		//}
		/*else if (m_velocity < 0)
		{
			if (map_data.tile[i_topBound][i_leftBound] != 0
				|| map_data.tile[i_topBound][i_rightBound] != 0)
			{
				m_playerPosition.y = (i_topBound + 1) * TILE_SIZE;
				m_velocity = 0;
			}
		}*/
	}

	//check horizontal

	/*i_leftBound = (m_playerPosition.x + m_velocity) / TILE_SIZE;
	i_rightBound = (m_playerPosition.x + width_min + m_velocity - 1) / TILE_SIZE;
	i_bottomBound = (m_playerPosition.y + height_min) / TILE_SIZE;
	i_topBound = (m_playerPosition.y) / TILE_SIZE;

	if (i_leftBound >= 0 && i_rightBound < MAX_MAP_X && i_topBound >= 0 && i_bottomBound < MAX_MAP_Y)
	{
		if (m_velocity < 0)
		{
			if (map_data.tile[i_topBound][i_rightBound] != 0
				|| map_data.tile[i_bottomBound][i_rightBound] != 0)
			{
				m_playerPosition.x = i_rightBound * TILE_SIZE;
				m_playerPosition.x -= (width_min + 1);
				m_playerSpeed = 0;
			}
		}
		else if (m_velocity > 0)
		{
			if (map_data.tile[i_topBound][i_leftBound] != 0
				|| map_data.tile[i_bottomBound][i_leftBound] != 0)
			{
				m_playerPosition.x = (i_leftBound + 1) * TILE_SIZE;
			}
		}
	}*/
	
}


