#include "GSMenu.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}) 
{
}


GSMenu::~GSMenu()
{
}

bool ResourceManagers::isMuted = false;

void GSMenu::Init()
{

	//Sound 
	if (!isMuted)
	{
		m_Sound = std::make_shared<Sound>("Data/Sounds/menuLoop.mp3");
		m_Sound->PlaySound();
	}
	Camera::GetInstance()->SetPosition({ 0, 0 });
	auto texture = ResourceManagers::GetInstance()->GetTexture("back1.tga");
	// background
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_play.tga");
	m_btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnPlay->SetSize(300 , 300);
	m_btnPlay->Set2DPosition((SCREEN_WIDTH - m_btnPlay->GetWidth()) / 2, (SCREEN_HEIGHT - m_btnPlay->GetHeight()) / 2 + 75);
	m_btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_LEVEL);
		});
	m_listButton.push_back(m_btnPlay);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_close.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(75, 75);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth(), 10);
	btnClose->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(btnClose);

	//Setting game
	texture = ResourceManagers::GetInstance()->GetTexture("button_setting.tga");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnOption->SetSize(200, 200);
	btnOption->Set2DPosition(m_btnPlay->Get2DPosition().x + m_btnPlay->GetWidth() + 50,
							(SCREEN_HEIGHT - btnOption->GetHeight()) / 2 + 75);
	btnOption->SetOnClick([this, texture]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
		});
	m_listButton.push_back(btnOption);

	//Character Seclection
	texture = ResourceManagers::GetInstance()->GetTexture("button_player.tga");
	m_btnCharacter_Selection = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnCharacter_Selection->SetSize(200, 200);
	m_btnCharacter_Selection->Set2DPosition(m_btnPlay->Get2DPosition().x - m_btnCharacter_Selection->GetWidth() - 50,
		(SCREEN_HEIGHT - m_btnCharacter_Selection->GetHeight()) / 2 + 75);
	m_btnCharacter_Selection->SetOnClick([this, texture]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CHARACTER);
		});
	m_listButton.push_back(m_btnCharacter_Selection);

	//GUIDE game
	texture = ResourceManagers::GetInstance()->GetTexture("button_help.tga");
	m_btnGuide = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnGuide->Set2DPosition(btnClose->Get2DPosition().x - m_btnGuide->GetWidth(), 3);
	m_btnGuide->SetSize(90 , 90);
	m_btnGuide->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_GUIDE);
		});
	m_listButton.push_back(m_btnGuide);

	// game title
	texture = ResourceManagers::GetInstance()->GetTexture("title.tga");
	m_gameTitle = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_gameTitle->SetSize(1409 , 179);
	m_gameTitle->Set2DPosition((SCREEN_WIDTH - m_gameTitle->GetWidth()) / 2, 200);

}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
	m_Sound->PauseSound();

}

void GSMenu::Resume()
{
	if(!isMuted)
		m_Sound->PlaySound();
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
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

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_gameTitle->Draw(renderer);
}


