#include "GSLevel.h"

GSLevel::GSLevel() : GameStateBase(StateType::STATE_LEVEL),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSLevel::~GSLevel()
{
}



void GSLevel::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("back1.tga");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnPlay->SetSize(150, 150);
	btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth()) / 2, (SCREEN_HEIDHT - btnPlay->GetHeight()) / 2);
	btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(btnPlay);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(50, 50);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth(), 10);
	btnClose->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(btnClose);

	//Setting game
	texture = ResourceManagers::GetInstance()->GetTexture("btn_settings.tga");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnOption->SetSize(50, 50);
	btnOption->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth() - 60, 10);
	btnOption->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
		});
	m_listButton.push_back(btnOption);

	//Show level
	texture = ResourceManagers::GetInstance()->GetTexture("background.tga");
	m_imglv = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_imglv->SetSize(SCREEN_WIDTH/10, SCREEN_HEIDHT/10);
	m_imglv->Set2DPosition(0, 0);

	//Btn prev
	texture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
	m_btnPrev = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnPrev->SetSize(100, 100);
	m_btnPrev->Set2DPosition(((SCREEN_WIDTH - m_btnPrev->GetWidth()) / 2) + 200, SCREEN_HEIDHT / 2 + 280);
	m_btnPrev->SetOnClick([]() {
		
		});
	m_listButton.push_back(m_btnPrev);

	//Btn next
	texture = ResourceManagers::GetInstance()->GetTexture("btn_next.tga");
	m_btnNext = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnNext->SetSize(100, 100);
	m_btnNext->Set2DPosition(((SCREEN_WIDTH - m_btnNext->GetWidth()) / 2) + 800 , SCREEN_HEIDHT / 2 + 280);
	m_btnNext->SetOnClick([]() {

		});
	m_listButton.push_back(m_btnNext);

	// game title
	///Set Font
	m_textColor = { 255, 255, 0 };
	m_textGameName = std::make_shared<Text>("Data/lazy.ttf", m_textColor);
	m_textGameName->SetSize(300, 50);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 300);
	m_textGameName->LoadFromRenderText("Your Game");
	m_Sound = std::make_shared<Sound>("Data/Sounds/Alarm01.wav");
	m_Sound->PlaySound();
}

void GSLevel::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSLevel::Pause()
{
	m_Sound->StopSound();

}

void GSLevel::Resume()
{
	m_Sound->PlaySound();
}


void GSLevel::HandleEvents()
{
}

void GSLevel::HandleKeyEvents(SDL_Event& e)
{
}

void GSLevel::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSLevel::HandleMouseMoveEvents(int x, int y)
{
}
//float time = 0.0f;
void GSLevel::Update(float deltaTime)
{
	time += deltaTime;
	//printf("DeltaTime = %f", deltaTime);
	if (time >= 1.5f)
	{
		time = 0.0f;
	}
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSLevel::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_textGameName->Draw(renderer);
}
