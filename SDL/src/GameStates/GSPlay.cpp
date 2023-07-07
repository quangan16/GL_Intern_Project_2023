#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "GameObject/Background.h"

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_01.tga");

	// background_1
	m_background = std::make_shared<Background>(texture, 10.0f, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	//background_2
	m_background_2 = std::make_shared<Background>(texture, 10.0f,SDL_FLIP_NONE);
	m_background_2->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background_2->Set2DPosition(m_background->Get2DPosition().x + (float)SCREEN_WIDTH, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

   // Animation 
	texture = ResourceManagers::GetInstance()->GetTexture("player.tga");
	obj = std::make_shared<SpriteAnimation>( texture, 1, 1, 1, 0.2f);
	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetSize(145/2, 120/2);
	obj->Set2DPosition(0, 700);
	
	Camera::GetInstance()->SetTarget(obj);
	m_listAnimation.push_back(obj);

	m_KeyPress = 0;
}

void GSPlay::Exit()
{
	
}


void GSPlay::Pause()
{

}
void GSPlay::Resume()
{
	
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(SDL_Event& e)
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

void GSPlay::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	switch (m_KeyPress)//Handle Key event
	{
	default:
		break;
	}
	
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

	//Player move when state started
	float x = 200 * deltaTime;
	if (obj->Get2DPosition().x <= 500.0f) {
		obj->Set2DPosition((float)obj->Get2DPosition().x + x, (float)obj->Get2DPosition().y);
	}
	else
	{
		obj->Set2DPosition((float)obj->Get2DPosition().x, (float)obj->Get2DPosition().y);
	}

	//Moving background
	m_background = std::get<0>(m_background->MovingBackGround(m_background, m_background_2));
	m_background_2 = std::get<1>(m_background_2->MovingBackGround(m_background, m_background_2));

	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	obj->Update(deltaTime);
	printf("%f, \n", obj->GetPosition().x);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	m_background_2->Draw(renderer);
	//m_score->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	obj->Draw(renderer);
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}
}