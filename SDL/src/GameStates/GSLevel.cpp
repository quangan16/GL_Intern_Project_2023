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

	if (!isMuted)m_Sound->PlaySound();
	auto texture = ResourceManagers::GetInstance()->GetTexture("back1.tga");

	// background
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	//slider
	texture = ResourceManagers::GetInstance()->GetTexture("slider.tga");
	m_slider = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_slider->SetSize(1000, 40);
	m_slider->Set2DPosition((SCREEN_WIDTH - m_slider->GetWidth())/2, 200);

	// Level 
	texture = ResourceManagers::GetInstance()->GetTexture("level_" + std::to_string(m_iMapTexture_index) + ".tga");
	m_levelPickCanvas = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_levelPickCanvas->SetSize(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 200 );
	m_levelPickCanvas->Set2DPosition((SCREEN_WIDTH - m_levelPickCanvas->GetWidth()) / 2, (SCREEN_HEIGHT - m_levelPickCanvas->GetHeight()) / 2);
	

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_close.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
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
	texture = ResourceManagers::GetInstance()->GetTexture("prev_map.tga");
	m_btnPrev = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnPrev->SetSize(200, 200);
	m_btnPrev->Set2DPosition(50, (SCREEN_HEIGHT - m_btnPrev->GetHeight())/2);
	m_btnPrev->SetOnClick([this, texture]() {
		if (m_iMapTexture_index > 1)
		{
			m_iMapTexture_index--;
		}
		else
		{
			m_iMapTexture_index = m_iMaptexturesCount;
		}
		std::string texture_path = "level_" + std::to_string(m_iMapTexture_index) + ".tga";
		m_levelPickCanvas->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture_path));
		m_textGameName->LoadFromRenderText("HIGH SCORE : " + std::to_string(m_Highscore[m_iMapTexture_index - 1]) + "%");
		});
	m_listButton.push_back(m_btnPrev);

	//Btn next
	texture = ResourceManagers::GetInstance()->GetTexture("next_map.tga");
	m_btnNext = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnNext->SetSize(200, 200);
	m_btnNext->Set2DPosition(SCREEN_WIDTH - m_btnNext->GetWidth() - 50, (SCREEN_HEIGHT - m_btnNext->GetHeight()) / 2);
	m_btnNext->SetOnClick([this, texture]() {
		if (m_iMapTexture_index < m_iMaptexturesCount)
		{
			m_iMapTexture_index++;
		}
		else
		{
			m_iMapTexture_index = 1;
		}
		std::string texture_path = "level_" + std::to_string(m_iMapTexture_index) + ".tga";
		m_levelPickCanvas->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture_path));
		m_textGameName->LoadFromRenderText("HIGH SCORE : " + std::to_string(m_Highscore[m_iMapTexture_index - 1]) + "%");
		});
	m_listButton.push_back(m_btnNext);

	//btn back
	texture = ResourceManagers::GetInstance()->GetTexture("back.tga");
	m_btnBack = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnBack->SetSize(80, 80);
	m_btnBack->Set2DPosition(20, 20);
	m_btnBack->SetOnClick([this, texture]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(m_btnBack);


	//Btn play
	texture = ResourceManagers::GetInstance()->GetTexture("button_play1.tga");
	m_btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnPlay->SetSize(200, 200);
	m_btnPlay->Set2DPosition((SCREEN_WIDTH - m_btnPlay->GetWidth())/2, (SCREEN_HEIGHT - m_btnPlay->GetHeight()) / 2 + 300);
	m_btnPlay->SetOnClick([this, texture]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(m_btnPlay);

	//High Process Text
	SDL_Color text_Color = { 255, 255, 255 };
	m_textGameName = std::make_shared<Text>("Data/PUSAB___.otf", text_Color);
	m_textGameName->SetSize(700, 70);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth()) / 2, m_slider->Get2DPosition().y + 100 );
	m_textGameName->LoadFromRenderText("HIGH SCORE : " + std::to_string(m_Highscore[m_iMapTexture_index - 1]) + "%");

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
	if(!isMuted)m_Sound->PlaySound();
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
	m_background->RGBEffect();
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	processBarWidth = m_Highscore[m_iMapTexture_index-1] * 9.8f;
}

void GSLevel::Draw(SDL_Renderer* renderer)
{
	
	m_background->Draw(renderer);
	m_levelPickCanvas->Draw(renderer);
	SDL_Rect foregroundRect = { m_slider->Get2DPosition().x + 10, m_slider->Get2DPosition().y + 5, processBarWidth, PROCESS_HEIGHT};
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color
	SDL_RenderFillRect(renderer, &foregroundRect);
	m_slider->DrawFixedObject(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_textGameName->Draw(renderer);
	
}
