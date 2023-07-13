#include "GSCharacter.h"

GSCharacter::GSCharacter() : GameStateBase(StateType::STATE_LEVEL),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{})
{
}


GSCharacter::~GSCharacter()
{
}



void GSCharacter::Init()
{
	m_iMapTexture_index = 1;
	m_iMaptexturesCount = 2;

	m_iCharacterTexture_index = 1;
	m_iCharactertexturesCount = 2;
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("back1.tga");

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
	//	GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
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

	//Show character
	texture = ResourceManagers::GetInstance()->GetTexture("player_cube_1.tga");
	m_imgchar = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_imgchar->SetSize(100, 100);
	m_imgchar->Set2DPosition(SCREEN_WIDTH / 2 - 550, SCREEN_HEIGHT / 2);

	//Btn prev
	texture = ResourceManagers::GetInstance()->GetTexture("button_leftarrow.tga");
	m_btnPrev = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnPrev->SetSize(100, 100);
	m_btnPrev->Set2DPosition(((SCREEN_WIDTH - m_btnPrev->GetWidth()) / 2) - 800, SCREEN_HEIGHT / 2);
	m_btnPrev->SetOnClick([this, texture]() {
		if (m_iCharacterTexture_index > 1)
		{
			m_iCharacterTexture_index--;
		}
		else
		{
			m_iCharacterTexture_index = m_iCharactertexturesCount;
		}
		std::string texture_path = "player_cube_" + std::to_string(m_iCharacterTexture_index) + ".tga";
		m_imgchar->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture_path));
		});
	m_listButton.push_back(m_btnPrev);

	//Btn next
	texture = ResourceManagers::GetInstance()->GetTexture("button_rightarrow.tga");
	m_btnNext = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnNext->SetSize(100, 100);
	m_btnNext->Set2DPosition(((SCREEN_WIDTH - m_btnNext->GetWidth()) / 2) - 200, SCREEN_HEIGHT / 2);
	m_btnNext->SetOnClick([this, texture]() {
		if (m_iCharacterTexture_index < m_iCharactertexturesCount)
		{
			m_iCharacterTexture_index++;
		}
		else
		{
			m_iCharacterTexture_index = 1;
		}
		std::string texture_path = "player_cube_" + std::to_string(m_iCharacterTexture_index) + ".tga";
		m_imgchar->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture_path));
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
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_LEVEL);
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
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(m_btnPlay);
}

void GSCharacter::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSCharacter::Pause()
{
	m_Sound->StopSound();

}

void GSCharacter::Resume()
{
	m_Sound->PlaySound();
}


void GSCharacter::HandleEvents()
{
}

void GSCharacter::HandleKeyEvents(SDL_Event& e)
{
}

void GSCharacter::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSCharacter::HandleMouseMoveEvents(int x, int y)
{
}
//float time = 0.0f;
void GSCharacter::Update(float deltaTime)
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

void GSCharacter::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_imgchar->Draw(renderer);
	m_textNext->Draw(renderer);
	m_textBack->Draw(renderer);
}
