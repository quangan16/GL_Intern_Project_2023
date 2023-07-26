#pragma once
#include<iostream>
#include "CMath.h"

//#include "Cube.h"
#include <list>
#include "Player.h"
#include <stack>
class Player;
struct SavePoint
{
	

	std::list<std::shared_ptr<Player>> m_savePointStack;
	float m_saveIntervalTime;
	float m_timeStamp;

	
	void PushSavePoint( std::shared_ptr<Player> _player);
	void PushSavePointOverTime( std::shared_ptr<Player> _player);
	void PopSavePoint();

	SavePoint() {

		m_saveIntervalTime = 3.0f;
		m_timeStamp = 0.0f;
	}
};