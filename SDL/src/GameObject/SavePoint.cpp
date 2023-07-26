#include "SavePoint.h"
#include "Player.h"

void SavePoint::PushSavePointOverTime( std::shared_ptr<Player> _player) {
	if (timer < m_timeStamp) return;
	m_timeStamp += m_saveIntervalTime;
	m_savePointStack.push_back(_player);
	if (m_savePointStack.size() > 5) {
		auto it = std::next(m_savePointStack.begin(), 1); 
		m_savePointStack.erase(it);
	}
	std::cout << m_savePointStack.size();
}

void SavePoint::PushSavePoint( std::shared_ptr<Player> _player) {
	
	m_savePointStack.push_back(_player);
	std::cout <<m_savePointStack.size()<<std::endl;
}

void SavePoint::PopSavePoint() {
	if (!m_savePointStack.empty()) {
		m_savePointStack.pop_back();
	}
}