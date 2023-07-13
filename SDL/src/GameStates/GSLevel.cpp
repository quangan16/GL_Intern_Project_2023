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
	m_iMapTexture_index = 1;
	m_iMaptexturesCount = 2;

	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play1.tga");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// play button
	//texture = ResourceManagers::GetInstance()->GetTexture("button_play.tga");
	//std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnPlay->SetSize(150, 150);
	//btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth()) / 2, (float)(SCREEN_HEIGHT - btnPlay->GetHeight()) / 2);
	//btnPlay->SetOnClick([]() {
	//	GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CHARACTER);
	//	});
	//m_listButton.push_back(btnPlay);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_close.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(50, 50);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth(), 10);
	btnClose->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(btnClose);

	//Setting game
	texture = ResourceManagers::GetInstance()->GetTexture("button_setting.tga");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnOption->SetSize(50, 50);
	btnOption->Set2DPosition((SCREEN_WIDTH - btnOption->GetWidth()) - 60, 10);
	btnOption->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
		});
	m_listButton.push_back(btnOption);

	//GUIDE game
	texture = ResourceManagers::GetInstance()->GetTexture("button_help.tga");
	m_btnGuide = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnGuide->Set2DPosition((SCREEN_WIDTH - m_btnGuide->GetWidth()) - 70, 10);
	m_btnGuide->SetSize(50, 50);
	m_btnGuide->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_GUIDE);
		});
	m_listButton.push_back(m_btnGuide);
	
	//Btn prev
	texture = ResourceManagers::GetInstance()->GetTexture("button_leftarrow.tga");
	m_btnPrev = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnPrev->SetSize(100, 100);
	m_btnPrev->Set2DPosition(50, SCREEN_HEIGHT / 2);
	m_btnPrev->SetOnClick([this, texture]() {
		if (m_iMapTexture_index > 1)
		{
			m_iMapTexture_index--;
		}
		else
		{
			m_iMapTexture_index = m_iMaptexturesCount;
		}
		std::string texture_path = "bg_play" + std::to_string(m_iMapTexture_index) + ".tga";
		//m_imglv->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture_path));
		m_background->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture_path));
		});
	m_listButton.push_back(m_btnPrev);

	//Btn next
	texture = ResourceManagers::GetInstance()->GetTexture("button_rightarrow.tga");
	m_btnNext = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnNext->SetSize(100, 100);
	m_btnNext->Set2DPosition(SCREEN_WIDTH - m_btnNext->GetWidth() - 50 , SCREEN_HEIGHT / 2);
	m_btnNext->SetOnClick([this, texture]() {
		if (m_iMapTexture_index < m_iMaptexturesCount)
		{
			m_iMapTexture_index++;
		}
		else
		{
			m_iMapTexture_index = 1;
		}
		std::string texture_path = "bg_play" + std::to_string(m_iMapTexture_index) + ".tga";
		//m_imglv->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture_path));
		m_background->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture_path));
		});
	m_listButton.push_back(m_btnNext);


	//Text back
	m_textColor = { 255, 255, 0 };
	m_textBack = std::make_shared<Text>("Data/xirod.otf", m_textColor);
	m_textBack->SetSize(150, 75);
	m_textBack->Set2DPosition(200, SCREEN_HEIGHT - 200);
	m_textBack->LoadFromRenderText("Back");
	//Btn back
	texture = ResourceManagers::GetInstance()->GetTexture("empty.tga");
	m_btnBack = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnBack->SetSize(200, 100);
	m_btnBack->Set2DPosition(200, SCREEN_HEIGHT - 200);
	m_btnBack->SetOnClick([this, texture]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(m_btnBack);

	//Text next
	m_textColor = { 255, 255, 0 };
	m_textNext = std::make_shared<Text>("Data/xirod.otf", m_textColor);
	m_textNext->SetSize(150, 75);
	m_textNext->Set2DPosition(SCREEN_WIDTH - m_textNext->GetWidth() - 200, SCREEN_HEIGHT - 200);
	m_textNext->LoadFromRenderText("Next");
	//Btn play
	texture = ResourceManagers::GetInstance()->GetTexture("empty.tga");
	m_btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnPlay->SetSize(200, 100);
	m_btnPlay->Set2DPosition(SCREEN_WIDTH - m_btnPlay->GetWidth() - 200, SCREEN_HEIGHT - 200);
	m_btnPlay->SetOnClick([this, texture]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CHARACTER);
		});
	m_listButton.push_back(m_btnPlay);
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
	m_textNext->Draw(renderer);
	m_textBack->Draw(renderer);
}
