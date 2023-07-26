#pragma once
#include<iostream>
#include "CMath.h"

#include "Player.h"
#include <list>
#include "Player.h"
#include <stack>

struct SavePoint
{
	

	std::list<PlayerSavePointData> m_savePointStack;
	float m_saveIntervalTime;
	float m_timeStamp;

	
	void PushSavePoint(const std::shared_ptr<Player>& _player);
	void PushSavePointOverTime(const std::shared_ptr<Player>& _player);
	void PopSavePoint();
	

	SavePoint() {

		m_saveIntervalTime = 5.0f;
		m_timeStamp = 0.0f;
	}
};