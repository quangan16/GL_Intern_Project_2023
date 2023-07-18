#include "GSMenu.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}

bool ResourceManagers::isMuted = false;

void GSMenu::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("back1.tga");
	m_texture = std::make_shared<TextureManager>();
	m_texture = texture;
	a = 256;
	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_play.tga");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnPlay->SetSize(150, 150);
	btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth()) / 2, (SCREEN_HEIGHT - btnPlay->GetHeight()) / 2);
	btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_LEVEL);
		});
	m_listButton.push_back(btnPlay);

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
	texture = ResourceManagers::GetInstance()->GetTexture("button_setting.tga");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnOption->SetSize(100, 100);
	btnOption->Set2DPosition((SCREEN_WIDTH - btnOption->GetWidth()) / 2, SCREEN_HEIGHT / 2 + 170);
	btnOption->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
		});
	m_listButton.push_back(btnOption);

	//GUIDE game
	texture = ResourceManagers::GetInstance()->GetTexture("button_help.tga");
	m_btnGuide = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnGuide->Set2DPosition((SCREEN_WIDTH - m_btnGuide->GetWidth()) / 2, SCREEN_HEIGHT / 2 + 280);
	m_btnGuide->SetSize(100, 100);
	m_btnGuide->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_GUIDE);
		});
	m_listButton.push_back(m_btnGuide);

	//Change size window
	texture = ResourceManagers::GetInstance()->GetTexture("button_windowsetting.tga");
	m_btnWindow = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnWindow->Set2DPosition(SCREEN_WIDTH - m_btnWindow->GetWidth() - 10, 10);
	m_btnWindow->SetSize(50, 50);
	m_btnWindow->SetOnClick([]() {

		});
	m_listButton.push_back(m_btnWindow);

	// game title
	///Set Font
	m_textColor = { 255, 255, 0 };
	m_textGameName = std::make_shared<Text>("Data/xirod.otf", m_textColor);
	m_textGameName->SetSize(1200, 150);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth()) / 2, SCREEN_HEIGHT / 2 - 400);
	m_textGameName->LoadFromRenderText("Geometry Dash");
	m_Sound = std::make_shared<Sound>("Data/Sounds/Alarm01.wav");
	m_Sound->PlaySound();
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
	m_Sound->StopSound();

}

void GSMenu::Resume()
{
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
float time = 0.0f;
int index = 0;
void GSMenu::Update(float deltaTime)
{
	time += deltaTime;

	//printf("DeltaTime = %f", deltaTime);
	if (time >= 1.5f)
	{
		time = 0.0f;
	}
	
	if (index > 2) index = 0;
	if (r == 255 && index == 0 || g == 255 && index == 1 || b == 255 && index == 2) index++;

	if (index == 0)
	{
		if (r == 255 || r < 2) interval *= -1;
		r += interval;
		printf("%d \n", r);
	}

	if (index == 1)
	{
		if (g == 255 || g < 2) interval *= -1;
		g += interval;
		printf("%d \n", r);
	}

	if (index == 2)
	{
		if (b == 255 || b < 2) interval *= -1;
		b += interval;
		printf("%d \n", r);
	}

	m_texture->setColor(r, g, b);
	m_background->SetTexture(m_texture);
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
	m_textGameName->Draw(renderer);
}


