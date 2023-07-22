#include "GSGuide.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"


GSGuide::GSGuide()
{
}


GSGuide::~GSGuide()
{
}


void GSGuide::Init()
{
	if (!isMuted)m_Sound->PlaySound();
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("back1.tga");

	// background
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// guide image
	texture = ResourceManagers::GetInstance()->GetTexture("guide_cube.tga");
	m_guide_Cube = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_guide_Cube->SetSize(676, 380);
	m_guide_Cube->Set2DPosition((SCREEN_WIDTH - m_guide_Cube->GetWidth())/2, 100);

	// guide ship
	texture = ResourceManagers::GetInstance()->GetTexture("guide_ship.tga");
	m_guide_Ship = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_guide_Ship->SetSize(676, 380);
	m_guide_Ship->Set2DPosition((SCREEN_WIDTH - m_guide_Cube->GetWidth()) / 2, 530);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("button_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		exit(0);
		});
	m_listButton.push_back(button);

	// button back
	texture = ResourceManagers::GetInstance()->GetTexture("back.tga");
	m_buttonBack = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_buttonBack->SetSize(80, 80);
	m_buttonBack->Set2DPosition(20, 20);
	m_buttonBack->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(m_buttonBack);

	//sound
}

void GSGuide::Exit()
{

}


void GSGuide::Pause()
{
	m_Sound->PauseSound();
}
void GSGuide::Resume()
{
	if (!isMuted) m_Sound->PlaySound();
}


void GSGuide::HandleEvents()
{
}

void GSGuide::HandleKeyEvents(SDL_Event& e)
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

void GSGuide::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSGuide::HandleMouseMoveEvents(int x, int y)
{
}

void GSGuide::Update(float deltaTime)
{
	m_background->RGBEffect();
	m_background->Update(deltaTime);
	switch (m_KeyPress)//Handle Key event
	{
	default:
		break;
	}

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	//for (auto it : m_listAnimation)
	//{
		//if (m_KeyPress == 1)
		//{

			//it->MoveLeft(deltaTime);
		//}
		//it->Update(deltaTime);
	//}

	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSGuide::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	//	obj->Draw(renderer);
	//for (auto it : m_listAnimation)
	{
		//it->Draw(renderer);
	}
	m_guide_Cube->Draw(renderer);
	m_guide_Ship->Draw(renderer);
}