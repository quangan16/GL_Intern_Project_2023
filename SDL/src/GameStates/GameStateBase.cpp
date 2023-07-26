#include "GameStateBase.h"
#include "GameStates/GSIntro.h"
#include "GSMenu.h"
#include "GSPlay.h"
#include "GSOption.h"
#include "GSGuide.h"
#include "GSLevel.h"
#include "GSCharacter.h"
#include "GSWin.h"
GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		//GSINTRO;
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		//GSMENU
		break;
	case StateType::STATE_PLAY:
		gs = std::make_shared<GSPlay>();
		//GSPLAY
		break;
	case StateType::STATE_OPTION:
		gs = std::make_shared<GSOption>();
		//GSOPTION
		break;
	case StateType::STATE_GUIDE:
		gs = std::make_shared<GSGuide>();
		//GSGUIDE
		break;
	case StateType::STATE_LEVEL:
		gs = std::make_shared<GSLevel>();
		//GSLEVEL
		break;
	case StateType::STATE_CHARACTER:
		gs = std::make_shared<GSCharacter>();
		//GSCHARACTER
		break;
	case StateType::STATE_WIN:
		gs = std::make_shared<GSWin>();
		break;
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}
