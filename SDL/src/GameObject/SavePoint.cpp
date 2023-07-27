#include "SavePoint.h"


void SavePoint::PushSavePointOverTime(const std::shared_ptr<Player>& _player) {
	if (timer < m_timeStamp) return;
	PlayerSavePointData data{
		
		_player->m_isJumping,
		_player->m_isFalling,
		_player->m_isOnGround,
		_player->m_jumpForce,
		_player->m_isAlive,
		_player->m_jumpBuffer,
		_player->m_changedState,
		_player->GetPlayerForm(),
		_player->GetPlayerPosition(),
		_player->GetPlayerRotation(),
		_player->GetDirectionY(),
		_player->GetPlayerVelocity(),
		_player->GetPlayerSpeed()
	};
	m_timeStamp += m_saveIntervalTime;
	m_savePointStack.push_back(data);
	if (m_savePointStack.size() > 5) {
		auto it = std::next(m_savePointStack.begin(), 1); 
		m_savePointStack.erase(it);
	}
	std::cout << m_savePointStack.size();
}

void SavePoint::PushSavePoint(const std::shared_ptr<Player>& _player) {
	PlayerSavePointData data{
		 
		_player->m_isJumping,
		_player->m_isFalling,
		_player->m_isOnGround,
		_player->m_jumpForce,
		_player->m_isAlive,
		_player->m_jumpBuffer,
		_player->m_changedState,
		_player->GetPlayerForm(),
		_player->GetPlayerPosition(),
		_player->GetPlayerRotation(),
		_player->GetDirectionY(),
		_player->GetPlayerVelocity(),
		_player->GetPlayerSpeed()
	};
	m_savePointStack.push_back(data);
	std::cout <<m_savePointStack.size()<<std::endl;
}

void SavePoint::PopSavePoint() {
	if (!m_savePointStack.empty()) {
		m_savePointStack.pop_back();
		std::cout << m_savePointStack.size();
	}
}