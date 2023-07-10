#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "GameObject/Background.h"
#include "GameObject/GameMap.h"

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("back1.tga");

	// background_1
	for (int i = 0; i < MAX_MAP_X * TILE_SIZE; i += SCREEN_WIDTH)
	{
		auto bg = std::make_shared<Background>(texture, 10.0f, SDL_FLIP_NONE);
		bg->SetSize(SCREEN_WIDTH,SCREEN_HEIGHT);
		bg->Set2DPosition(i, 0);
		m_listBackground.push_back(bg);
	}

	
	//Map
	m_gameMap = std::make_shared<GameMap>();
	m_gameMap->LoadMap("Data/map01.dat");

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(Camera::GetInstance()->GetViewBox().x + SCREEN_WIDTH , 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

   // Animation 
	//texture = ResourceManagers::GetInstance()->GetTexture("player.tga");
	//obj = std::make_shared<SpriteAnimation>( texture, 1, 1, 1, 0.2f);
	//obj->SetFlip(SDL_FLIP_HORIZONTAL);
	//obj->SetSize(145/2, 120/2);
	//obj->Set2DPosition(0, 700);
	//
	
	//m_listAnimation.push_back(obj);

	//Init Player

	texture = ResourceManagers::GetInstance()->GetTexture("player_cube_1.tga");
	m_playerSprite = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_player = std::make_shared<Cube>(-200.0f, 700.0f, 0.0, 1, m_gravity, texture);
	m_player->SetPlayerSprite(80, 80, m_playerSprite);
	Camera::GetInstance()->SetTarget(m_playerSprite);
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
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) 
	//For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
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
		case SDLK_SPACE:
			m_KeyPress != 1 << 4;
			if (!isJumping) // Only jump if the player is not already jumping
			{
				m_player->SetPlayerVelocity(jumpForce);
				float jumpHeight = 300.0f;
				isJumping = true;
				std::cout << isJumping;
				std::cout << m_player->GetPlayerPosition().y<<std::endl;
				jumpBoundY = m_player->GetPlayerJumpBoundY(jumpHeight);
				
			}
			else if (isFalling) {
				jumpBuffer = true;
			}
			
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
	std::cout << m_player->GetPlayerPosition().y<<std::endl;
	m_player->RunIntoScene(m_readyPos, deltaTime);
	
	
	m_player->ApplyGravity( m_gravity, isJumping, isFalling, isOnGround, deltaTime);
	if (isJumping == true) {
		m_player->MoveUp(jumpForce, m_gravity, isJumping, isFalling, isOnGround, jumpBoundY, jumpBuffer, deltaTime);
	}
	m_player->UpdatePlayerPos(deltaTime);
	m_player->UpdatePlayerSprite(m_playerSprite);
	
	
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
			
			it->MoveLeft(deltaTime);
		}
		it->Update(deltaTime);
	}

	

	//Moving background
	m_background = std::get<0>(m_background->MovingBackGround(m_background, m_background_2));
	//m_background_2 = std::get<1>(m_background_2->MovingBackGround(m_background, m_background_2));

	//Update position of camera
	Camera::GetInstance()->Update(deltaTime);
	/*obj->update(deltatime);*/
	//printf("%f, \n", obj->GetPosition().x);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	for (auto it : m_listBackground)
	{
		it->Draw(renderer);
	}
	m_gameMap->DrawMap(renderer);
	//m_score->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	//obj->Draw(renderer);
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}

	
	m_playerSprite->Draw(renderer);


}