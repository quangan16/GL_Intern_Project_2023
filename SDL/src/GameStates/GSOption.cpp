#include "GSOption.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "SDL_mixer.h"


GSOption::GSOption()
{
}


GSOption::~GSOption()
{
}

void GSOption::Init()
{
	//sound
	if(!isMuted)m_Sound->PlaySound();
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("back1.tga");

	// background
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("button_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// back button
	texture = ResourceManagers::GetInstance()->GetTexture("back.tga");
	m_backButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_backButton->SetSize(80, 80);
	m_backButton->Set2DPosition(20, 20);
	m_backButton->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(m_backButton);
	//sound
	Mix_Music* music = Mix_LoadMUS("");
	if (music == nullptr) {

	}
	Mix_PlayMusic(music, -1);

	//onoffmusic
	//texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
	if (isMuted)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("button_musicoff.tga");
	}
	else
	{
		texture = ResourceManagers::GetInstance()->GetTexture("button_musicon.tga");

	}

	//Muted button
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(100, 100);
	button->Set2DPosition((SCREEN_WIDTH - button->GetWidth())/2, (SCREEN_HEIGHT - button->GetHeight()) / 2);
	button->SetOnClick([this, texture]() {
		if (isMuted)
		{
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("button_musicon.tga"));
			isMuted = false;
			m_Sound->PlaySound();
		}
		else if(!isMuted)
		{
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("button_musicoff.tga"));
			isMuted = true;
			m_Sound->PauseSound();
		}
	});
	m_listButton.push_back(button);

	//slider volume
	//volumeBarWidth = (currentVolume * VOLUME_WIDTH) / maxVolume;

	m_KeyPress = 0;
}

void GSOption::Exit()
{

}


void GSOption::Pause()
{
	m_Sound->PauseSound();
}
void GSOption::Resume()
{
	if (!isMuted) m_Sound->PlaySound();
}


void GSOption::HandleEvents()
{
}

void GSOption::HandleKeyEvents(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			m_KeyPress |= 1 << 3;
			break;
		case SDLK_DOWN:
			m_KeyPress |= 1 << 1;
			break;
		case SDLK_LEFT:
			m_KeyPress |= 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress |= 1 << 2;
			break;
		default:
			break;
		}

	}
	////Key Up
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_KeyPress ^= 1;
			break;
		case SDLK_DOWN:
			m_KeyPress ^= 1 << 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case SDLK_UP:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}

	}
}

void GSOption::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSOption::HandleMouseMoveEvents(int x, int y)
{
		
}

void GSOption::Update(float deltaTime)
{
	switch (m_KeyPress)//Handle Key event
	{
	default:
		break;
	}
	m_background->RGBEffect();
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		if (m_KeyPress == 1)
		{

			//it->MoveLeft(deltaTime);
		}
		it->Update(deltaTime);
	}

	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSOption::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	//m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	//	obj->Draw(renderer);
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}
}
