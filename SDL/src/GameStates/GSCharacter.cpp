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

	//Show character cube
	texture = ResourceManagers::GetInstance()->GetTexture("player_cube_" + std::to_string(m_iCharacterTexture_index) + ".tga");
	m_img_Cube = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_img_Cube->SetSize(100, 100);
	m_img_Cube->Set2DPosition(SCREEN_WIDTH / 2 - 50, 100);

	//Show character ship
	texture = ResourceManagers::GetInstance()->GetTexture("player_ship_" + std::to_string(m_iShipTexture_index) + ".tga");
	m_img_Ship = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_img_Ship->SetSize(100, 100);
	m_img_Ship->Set2DPosition(SCREEN_WIDTH / 2 - 50, 300);

	//Show character wave
	texture = ResourceManagers::GetInstance()->GetTexture("player_wave_" + std::to_string(m_iShipTexture_index) + ".tga");
	m_img_Wave = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_img_Wave->SetSize(100, 100);
	m_img_Wave->Set2DPosition(SCREEN_WIDTH / 2 - 50, 500);

	//Btn prev Cube
	texture = ResourceManagers::GetInstance()->GetTexture("button_leftarrow.tga");
	m_btnPrev_Cube = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnPrev_Cube->SetSize(100, 100);
	m_btnPrev_Cube->Set2DPosition(m_img_Cube->Get2DPosition().x - m_img_Cube->GetWidth() - 20, 100);
	m_btnPrev_Cube->SetOnClick([this, texture]() {
		if (m_iCharacterTexture_index > 1)
		{
			m_iCharacterTexture_index--;
		}
		else
		{
			m_iCharacterTexture_index = m_iCharactertextures_count;
		}
		printf("%d \n", m_iCharacterTexture_index);
		std::string texture_path = "player_cube_" + std::to_string(m_iCharacterTexture_index) + ".tga";
		m_img_Cube->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture_path));
		});
	m_listButton.push_back(m_btnPrev_Cube);

	//Btn next Cube
	texture = ResourceManagers::GetInstance()->GetTexture("button_rightarrow.tga");
	m_btnNext_Cube = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnNext_Cube->SetSize(100, 100);
	m_btnNext_Cube->Set2DPosition(m_img_Cube->Get2DPosition().x + m_img_Cube->GetWidth() + 20, 100);
	m_btnNext_Cube->SetOnClick([this, texture]() {
		if (m_iCharacterTexture_index < m_iCharactertextures_count)
		{
			m_iCharacterTexture_index++;
		}
		else
		{
			m_iCharacterTexture_index = 1;
		}
		printf("%d \n", m_iCharacterTexture_index);
		std::string texture_path = "player_cube_" + std::to_string(m_iCharacterTexture_index) + ".tga";
		m_img_Cube->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture_path));
		});
	m_listButton.push_back(m_btnNext_Cube);

	//Btn prv Ship
	texture = ResourceManagers::GetInstance()->GetTexture("button_leftarrow.tga");
	m_btnPrev_Ship = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnPrev_Ship->SetSize(100, 100);
	m_btnPrev_Ship->Set2DPosition(m_img_Cube->Get2DPosition().x - m_img_Cube->GetWidth() - 20, 300);
	m_btnPrev_Ship->SetOnClick([this, texture]() {
		if (m_iShipTexture_index > 1)
		{
			m_iShipTexture_index--;
		}
		else
		{
			m_iShipTexture_index = m_iShipTexture_count;
		}
		printf("%d \n", m_iCharacterTexture_index);
		std::string texture_path = "player_ship_" + std::to_string(m_iShipTexture_index) + ".tga";
		m_img_Ship->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture_path));
		});
	m_listButton.push_back(m_btnPrev_Ship);

	//Btn next Ship
	texture = ResourceManagers::GetInstance()->GetTexture("button_rightarrow.tga");
	m_btnNext_Ship = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnNext_Ship->SetSize(100, 100);
	m_btnNext_Ship->Set2DPosition(m_img_Cube->Get2DPosition().x + m_img_Cube->GetWidth() + 20, 300);
	m_btnNext_Ship->SetOnClick([this, texture]() {
		if (m_iShipTexture_index < m_iShipTexture_count)
		{
			m_iShipTexture_index++;
		}
		else
		{
			m_iShipTexture_index = 1;
		}
		printf("%d \n", m_iCharacterTexture_index);
		std::string texture_path = "player_ship_" + std::to_string(m_iShipTexture_index) + ".tga";
		m_img_Ship->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture_path));
		});
	m_listButton.push_back(m_btnNext_Ship);

	//Btn prev Wave
	texture = ResourceManagers::GetInstance()->GetTexture("button_leftarrow.tga");
	m_btnPrev_Wave = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnPrev_Wave->SetSize(100, 100);
	m_btnPrev_Wave->Set2DPosition(m_img_Cube->Get2DPosition().x - m_img_Cube->GetWidth() - 20, 500);
	m_btnPrev_Wave->SetOnClick([this, texture]() {
		if (m_iWaveTexture_index > 1)
		{
			m_iWaveTexture_index--;
		}
		else
		{
			m_iWaveTexture_index = m_iWaveTexture_count;
		}
		printf("%d \n", m_iCharacterTexture_index);
		std::string texture_path = "player_wave_" + std::to_string(m_iWaveTexture_index) + ".tga";
		m_img_Wave->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture_path));
		});
	m_listButton.push_back(m_btnPrev_Wave);

	//Btn next Wave
	texture = ResourceManagers::GetInstance()->GetTexture("button_rightarrow.tga");
	m_btnNext_Wave = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnNext_Wave->SetSize(100, 100);
	m_btnNext_Wave->Set2DPosition(m_img_Cube->Get2DPosition().x + m_img_Cube->GetWidth() + 20, 500);
	m_btnNext_Wave->SetOnClick([this, texture]() {
		if (m_iWaveTexture_index < m_iWaveTexture_count)
		{
			m_iWaveTexture_index++;
		}
		else
		{
			m_iWaveTexture_index = 1;
		}
		printf("%d \n", m_iCharacterTexture_index);
		std::string texture_path = "player_wave_" + std::to_string(m_iWaveTexture_index) + ".tga";
		m_img_Wave->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture_path));
		});
	m_listButton.push_back(m_btnNext_Wave);

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

	m_img_Cube->Draw(renderer);
	m_img_Ship->Draw(renderer);
	m_img_Wave->Draw(renderer);


	m_textNext->Draw(renderer);
	m_textBack->Draw(renderer);
}
