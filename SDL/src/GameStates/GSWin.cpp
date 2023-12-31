#include "GSWin.h"

GSWin::GSWin() : GameStateBase(StateType::STATE_WIN),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{})
{
}


GSWin::~GSWin()
{
}

void GSWin::Init()
{
	//Sound 
	m_Sound = std::make_shared<Sound>("Data/Sounds/menuLoop.mp3");
	Camera::GetInstance()->SetPosition({ 0, 0 });
	auto texture = ResourceManagers::GetInstance()->GetTexture("back1.tga");
	// background
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_play.tga");
	m_btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnPlay->SetSize(250, 250);
	m_btnPlay->Set2DPosition((SCREEN_WIDTH - m_btnPlay->GetWidth()) / 2, (SCREEN_HEIGHT - m_btnPlay->GetHeight()) / 2);
	m_btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_LEVEL);
		});
	m_listButton.push_back(m_btnPlay);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_close.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(50, 50);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth(), 10);
	btnClose->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(btnClose);

	//Setting game
	texture = ResourceManagers::GetInstance()->GetTexture("Replay.tga");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnOption->SetSize(150, 150);
	btnOption->Set2DPosition(m_btnPlay->Get2DPosition().x + m_btnPlay->GetWidth() + 50,
		(SCREEN_HEIGHT - btnOption->GetHeight()) / 2);
	btnOption->SetOnClick([this, texture]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(btnOption);

	//Character Seclection
	texture = ResourceManagers::GetInstance()->GetTexture("Menu.tga");
	m_btnCharacter_Selection = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnCharacter_Selection->SetSize(150, 150);
	m_btnCharacter_Selection->Set2DPosition(m_btnPlay->Get2DPosition().x - m_btnCharacter_Selection->GetWidth() - 50,
		(SCREEN_HEIGHT - m_btnCharacter_Selection->GetHeight()) / 2);
	m_btnCharacter_Selection->SetOnClick([this, texture]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(m_btnCharacter_Selection);

	//GUIDE game
	texture = ResourceManagers::GetInstance()->GetTexture("button_help.tga");
	m_btnGuide = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnGuide->Set2DPosition(btnClose->Get2DPosition().x - 70, 5);
	m_btnGuide->SetSize(60, 60);
	m_btnGuide->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_GUIDE);
		});
	m_listButton.push_back(m_btnGuide);

	// game title
	texture = ResourceManagers::GetInstance()->GetTexture("Complete.tga");
	m_gameTitle = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_gameTitle->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_gameTitle->Set2DPosition((SCREEN_WIDTH - m_gameTitle->GetWidth()) / 2, 0);

}

void GSWin::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSWin::Pause()
{
	m_Sound->PauseSound();

}

void GSWin::Resume()
{
	if (!isMuted)
		m_Sound->PlaySound();
}


void GSWin::HandleEvents()
{
}

void GSWin::HandleKeyEvents(SDL_Event& e)
{
}

void GSWin::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSWin::HandleMouseMoveEvents(int x, int y)
{
}

void GSWin::Update(float deltaTime)
{
	/*if (isMuted) m_Sound->PauseSound();
	else m_Sound->PlaySound()*/;
	m_background->RGBEffect();
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSWin::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_gameTitle->Draw(renderer);
}


