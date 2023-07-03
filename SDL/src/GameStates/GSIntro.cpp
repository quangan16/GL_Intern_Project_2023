#include "GSIntro.h"
#include "GameManager/ResourceManagers.h"
#include "GameObject/Define.h"
GSIntro::GSIntro() : GameStateBase(StateType::STATE_INTRO), m_time(0.0f)
{
}


GSIntro::~GSIntro()
{
}


void GSIntro::Init()
{

	auto texture = ResourceManagers::GetInstance()->GetTexture("logo1.tga");

	m_logo = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_logo->SetSize(150, 150);
	m_logo->Set2DPosition((float)(SCREEN_WIDTH - m_logo->GetWidth())/2 , (float)(SCREEN_HEIDHT - m_logo->GetHeight())/2); 
}

void GSIntro::Exit()
{
}


void GSIntro::Pause()
{
}

void GSIntro::Resume()
{

}


void GSIntro::HandleEvents()
{
}

void GSIntro::HandleKeyEvents(SDL_Event& e)
{
}

void GSIntro::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
}

void GSIntro::HandleMouseMoveEvents(int x, int y)
{
}

void GSIntro::Update(float deltaTime)
{
	m_time += deltaTime;
	//printf("DeltaTime = %f", deltaTime);
	if (m_time > 1.5)
	{
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		m_time = 0;
	}
}

void GSIntro::Draw(SDL_Renderer* renderer)
{
	m_logo->Draw(renderer);
}
