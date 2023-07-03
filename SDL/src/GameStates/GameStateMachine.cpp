
#include "GameStateMachine.h"
#include "GameStateBase.h"
GameStateMachine::GameStateMachine() : m_running(true), m_pActiveState(nullptr), m_pNextState(nullptr), m_fullscreen(false)
{
}


GameStateMachine::~GameStateMachine()
{
}


void GameStateMachine::Cleanup()
{
	// cleanup the all states
	while (!m_StateStack.empty()) {
		m_StateStack.back()->Exit();
		m_StateStack.pop_back();
	}
}

void GameStateMachine::ChangeState(StateType state)
{
	std::shared_ptr<GameStateBase> nextState = GameStateBase::CreateState(state);
	ChangeState(nextState);
}

void GameStateMachine::ChangeState(std::shared_ptr<GameStateBase> state)
{
	m_pNextState = state;
}

void GameStateMachine::PushState(StateType state)
{
	std::shared_ptr<GameStateBase> nextState = GameStateBase::CreateState(state);
	// pause current state
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Pause();
	}

	m_pNextState = nextState;
}

void GameStateMachine::PopState()
{
	// cleanup the current state
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Exit();
		m_StateStack.pop_back();
	}

	// resume previous state
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Resume();
		m_pActiveState = m_StateStack.back();
	}
}

void  GameStateMachine::PerformStateChange()
{
	if (m_pNextState != 0)
	{
		if (m_StateStack.empty() == false) {
			if (m_pActiveState->GetGameStateType() == StateType::STATE_INTRO)
			{
				// Cleanup Intro state
				m_pActiveState->Exit();
				m_StateStack.pop_back();
			}
			else
			{
				// Pause other states
				m_pActiveState->Pause();
			}
		}

		// store and init the new state
		m_StateStack.push_back(m_pNextState);
		m_StateStack.back()->Init();
		m_pActiveState = m_pNextState;
	}

	m_pNextState = 0;
}