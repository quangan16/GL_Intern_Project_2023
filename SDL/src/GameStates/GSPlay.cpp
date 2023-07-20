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
	auto texture = ResourceManagers::GetInstance()->GetTexture("backx2.tga");
	texture->setColor(148, 34, 224);
	texture->SetAlpha(500);
	// background_1
	for (int i = 0; i < MAX_MAP_X * TILE_SIZE; i += SCREEN_WIDTH)
	{
		auto bg = std::make_shared<Background>(texture, 10.0f, SDL_FLIP_NONE);
		bg->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT * 2);
		bg->Set2DPosition(i, 0);
		m_listBackground.push_back(bg);
	}

	m_color = std::make_shared<SDL_Color>();

	//Map
	m_gameMap = std::make_shared<GameMap>();
	m_gameMap->LoadMap("Data/map01.dat");
	m_gameMap->DrawMap();


	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH -100 , 10);
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
	//Cube
	/*texture = ResourceManagers::GetInstance()->GetTexture("player_cube_1.tga");
	m_playerSprite = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_player = std::make_shared<Cube>(Vector2(-200.0f, 300.0f), 0.0, 1, 0.0, texture);
	m_player->SetPlayerSprite(128, 128, m_playerSprite);
	m_playerCollider = m_player->GetCollider();
	m_playerCollider->SetSize(90, 90);
	Camera::GetInstance()->SetTarget(m_playerSprite);*/

	//Ship
	texture = ResourceManagers::GetInstance()->GetTexture("ship_26.png");
	m_playerSprite = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_player = std::make_shared<Ship>(Vector2(-200.0f, 300.0f), 0.0, 1, 0.0, texture);
	m_player->SetPlayerSprite(90, 60, m_playerSprite);
	m_playerCollider = m_player->GetCollider();
	m_playerCollider->SetSize(90, 90);
	Camera::GetInstance()->SetTarget(m_playerSprite);

	//Arrow
	/*texture = ResourceManagers::GetInstance()->GetTexture("wave_13.png");
	m_playerSprite = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_player = std::make_shared<Wave>(Vector2(-200.0f, 300.0f), 0.0, 1, 0.0, texture);
	m_player->SetPlayerSprite(90, 60, m_playerSprite);
	m_playerCollider = m_player->GetCollider();
	m_playerCollider->SetSize(90, 90);
	Camera::GetInstance()->SetTarget(m_playerSprite);*/



	//Test Colliders
	texture = ResourceManagers::GetInstance()->GetTexture("collider_border.tga");
	/*m_collider1 = std::make_shared<BoxCollider2D>(ColliderType::GROUND, Vector2(0.0f, 500.0f), true, 5000.0f, 410.0f, texture, SDL_FLIP_NONE);
	m_collider2 = std::make_shared<BoxCollider2D>(ColliderType::GROUND, Vector2(5100.0f, 500.0f), true, 5000.0f, 410.0f, texture, SDL_FLIP_NONE);
	m_colliderList.push_back(m_collider2);
	m_colliderList.push_back(m_collider1);*/


	m_playerCollider = m_player->GetCollider();

	//Dummy ground
	//m_ground = std::make_shared<Player>(Vector2(0.0f, 400.0f), 480.0f, 210.0f);

	for (auto& it : m_gameMap->tile_map_)
	{
		m_colliderList.push_back(it);
	}

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
	if (m_KeyPress & (1 << 4))
	{
		isFly = true;
		std::cout << "lol";
		/*if (isFalling) {
			jumpBuffer = true;
		}*/
	}

}

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN ) 
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
			m_KeyPress |= 1 << 4;
			OnButtonPressed = true;
			m_onButtonPressed = true;
			if (!m_player->m_isJumping) // Only jump if the player is not already jumping
			{
				if (std::dynamic_pointer_cast<Cube>(m_player) != NULL) {
					m_player->SetPlayerVelocity(m_player->m_jumpForce);
					float jumpHeight = JUMP_HEIGHT;
					m_player->m_isJumping = true;
				}
				if (std::dynamic_pointer_cast<Ship>(m_player) != NULL) {
					m_player->m_jumpForce = 5000;
				}
			}
			else if (m_player->m_isFalling) {
				jumpBuffer = true;
			}

			
			break;


		default:
			break;
		}

	}
	////Key Up
	else if (e.type == SDL_KEYUP )
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
		case SDLK_SPACE:
			m_KeyPress ^= 1 << 4;
			OnButtonPressed = false;
			m_onButtonPressed = false;
			if (std::dynamic_pointer_cast<Ship>(m_player) != NULL && !m_player->m_isFalling) {
				m_player->m_jumpForce = 5000;
			}
			/*m_player->m_isJumping = false;
			m_player->m_isFalling = true;*/
			break;
			if (isShip)
			{
				isFly = false;
			}
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

void GSPlay::PlayerTransform()
{
	
}

void GSPlay::Update(float deltaTime)
{
	
	try {
		HandleEvents();
	
	m_player->RunIntoScene(m_readyPos, deltaTime);
	m_player->ApplyGravity(m_gravity, deltaTime);
	m_player->SetPlayerPosition(m_player->GetPlayerPosition().x + 1000.0f * deltaTime, m_player->GetPlayerPosition().y);
	//std::cout << OnButtonPressed << std::endl;
	m_player->MoveUp(m_gravity, m_onButtonPressed, jumpBuffer, deltaTime);
	//std::cout << OnButtonPressed << std::endl;
	
	m_player->FixRotationOnGround(deltaTime);
	m_player->Rotate(315.0, deltaTime);
	Map map_data = m_gameMap->getMap();
	m_player->UpdatePlayerPos(deltaTime);
	m_player->UpdatePlayerSprite(m_playerSprite);
	/*for (const auto& collider : m_colliderList) {
		m_player->OnCollisionStay(collider, isFalling);
	}*/
	m_player->UpdatePlayerColliderState();
	

	for (const auto& collider : m_colliderList) {
		if (m_player->OnCollisionStay(collider)) {
			m_player->m_isOnGround = true;
			m_player->OnGround();
			
			break; // Exit the loop if ground collision is detected with any collider
		}
		else {
			m_player->m_isOnGround = false;
			//m_player->m_isFalling = true;
		}
	}
	
	/*for (const auto& collider : m_colliderList) {
		m_player->OnCollisionStay(collider, isOnGround, isFalling);
	}*/
	/*m_player->OnCollisionStay(m_collider2, isOnGround, isFalling);
	m_player->OnCollisionStay(m_collider1, isOnGround, isFalling);*/
	
	
	//m_player->OnGround(isJumping, isFalling, jumpBuffer, isOnGround);
	m_player->Die();
		
	}
	
	catch (std::exception_ptr e) {
		
	}
	//std::cout << m_player->GetPlayerVelocity()<<std::endl;
	//std::cout << m_collider1->GetColliderPosition().y;
	std::cout << "isFalling " << m_player->m_isFalling << std::endl;
	//std::cout << "isJumping " << m_player->m_isJumping << std::endl;
	//std::cout << "isOnground " << m_player->m_isOnGround << std::endl;
	//std::cout << "direction " << m_player->GetDirectionY() << std::endl;
	//std::cout << "jumpBuffer " << jumpBuffer << std::endl;
	//std::cout << "Number of coliders: " << m_colliderList.size()<<std::endl;
	//std::cout << OnButtonPressed << std::endl;
	//std::cout << m_playerCollider->GetWidth() << std::endl;
	

	

	/*for (auto it : m_gameMap->tile_map_)
	{
		if (m_playerCollider->CheckCollision(it))
		{
			m_player->SetPlayerPosition(m_player->GetPlayerPosition().x, it->GetColliderPosition().y - TILE_SIZE);
			m_player->SetPlayerVelocity(0.0f);
			isJumping = false;
		}
	}*/


	


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

	//Process bar
	if (processBarWidth >= PROCESS_WIDTH) {
		currentProcess = currentProcess;
		processBarWidth = PROCESS_WIDTH;
	}
	else {
		currentProcess = currentProcess + deltaTime;
		processBarWidth = (currentProcess * PROCESS_WIDTH) / maxProcess;
	}

	//Moving background
	//m_background = std::get<0>(m_background->MovingBackGround(m_background, m_background_2));
	//m_background_2 = std::get<1>(m_background_2->MovingBackGround(m_background, m_background_2));

	//Update position of camera
	Camera::GetInstance()->Update(deltaTime);
	Camera::GetInstance()->GetPosition();
	/*obj->update(deltatime);*/
	//printf("%f, \n", obj->GetPosition().x);
	//std::system("cls");
	
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	for (auto it : m_listBackground)
	{
		it->Draw(renderer);
	}

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
	//draw player
	m_playerSprite->Draw(renderer);
	for (auto it : m_colliderList) {
		it->Draw(renderer);
	}

	m_playerCollider->Draw(renderer);

	SDL_Rect backgroundRect = { SCREEN_WIDTH / 2 - 250, PROCESS_PADDING + 10, PROCESS_WIDTH, PROCESS_HEIGHT };
	SDL_Rect foregroundRect = { SCREEN_WIDTH / 2 - 250, PROCESS_PADDING + 10, processBarWidth, PROCESS_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
	SDL_RenderFillRect(renderer, &backgroundRect);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color
	SDL_RenderFillRect(renderer, &foregroundRect);


}