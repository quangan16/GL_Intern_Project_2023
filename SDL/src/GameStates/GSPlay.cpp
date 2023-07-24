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
	canDrawEvent = true;
	timer = 0.0f;
	aliveTime = 0.0f;
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
	//Test jump trigger
	/*{
		
		texture = ResourceManagers::GetInstance()->GetTexture("circleBorder.tga");
		m_trigger1 = std::make_shared<CircleCollider2D>(ColliderType::JUMP_BOOST, Vector2(1200, 500), true, TILE_SIZE, texture, SDL_FLIP_NONE);
		m_trigger1->SetFlip(SDL_FLIP_HORIZONTAL);
		m_trigger1->SetSize(90, 90);
		m_trigger1->Set2DPosition(640, 800);
	}*/
	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("button_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH -100 , 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		
		g_stateControllerPtr.reset();
		g_stateControllerPtr = nullptr;
		
		});
	m_listButton.push_back(button);
	
	
	//Slider
	texture = ResourceManagers::GetInstance()->GetTexture("slider.tga");
	m_slider = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_slider->SetSize(500, 20);
	m_slider->Set2DPosition(SCREEN_WIDTH / 2 - 250, 20);

	//Process
	SDL_Color text_Color = {255, 255, 255};
	m_Process = std::make_shared<Text>("Data/PUSAB___.otf", text_Color);
	m_Process->SetSize(70, 50);
	m_Process->Set2DPosition(m_slider->Get2DPosition().x + m_slider->GetWidth() + 10, 10);
	m_Process->LoadFromRenderText(std::to_string(currentProcess));

	//Init Player
	//Cube
	//std::cout << m_iCharacterTexture_index << std::endl;
	texture = ResourceManagers::GetInstance()->GetTexture("player_cube_" + std::to_string(m_iCharacterTexture_index) +".tga");
	m_playerSprite = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_player = std::make_shared<Cube>(Vector2(-200.0f, 500.0f), 0.0, 1, 0.0, texture);
	m_player->SetPlayerSprite(TILE_SIZE, TILE_SIZE, m_playerSprite);
	m_playerCollider = m_player->GetCollider();
	m_playerCollider->SetSize(TILE_SIZE, TILE_SIZE);
	m_player->m_changedState = false;
	Camera::GetInstance()->SetTarget(m_playerSprite);

	//Ship
	/*texture = ResourceManagers::GetInstance()->GetTexture("player_ship_1.tga");
	m_playerSprite = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_player = std::make_shared<Ship>(Vector2(-200.0f, 500.0f), 0.0, 1, 0.0, texture);
	m_player->SetPlayerSprite(90, 60, m_playerSprite);
	m_playerCollider = m_player->GetCollider();
	m_playerCollider->SetSize(90, 90);
	Camera::GetInstance()->SetTarget(m_playerSprite);*/
	
	//Arrow
	/*texture = ResourceManagers::GetInstance()->GetTexture("wave_13.png");
	m_playerSprite = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_player = std::make_shared<Wave>(Vector2(-200.0f, 300.0f), 0.0, 1, 0.0, texture);
	m_player->SetPlayerSprite(90, 60, m_playerSprite);
	m_playerCollider = m_player->GetCollider();
	m_playerCollider->SetSize(90, 90);
	Camera::GetInstance()->SetTarget(m_playerSprite);*/



	//Test Colliders
	/*texture = ResourceManagers::GetInstance()->GetTexture("collider_border.tga");
	m_collider1 = std::make_shared<BoxCollider2D>(ColliderType::GROUND, Vector2(0.0f, 500.0f), true, 5000.0f, 410.0f, texture, SDL_FLIP_NONE);
	m_collider2 = std::make_shared<BoxCollider2D>(ColliderType::GROUND, Vector2(5100.0f, 500.0f), true, 5000.0f, 410.0f, texture, SDL_FLIP_NONE);
	m_colliderList.push_back(m_collider2);
	m_colliderList.push_back(m_collider1);*/


	m_playerCollider = m_player->GetCollider();

	//Dummy ground
	//m_ground = std::make_shared<Player>(Vector2(0.0f, 400.0f), 480.0f, 210.0f);

	for (auto& it : m_gameMap->tile_map_box)
	{
		m_boxColliderList.push_back(it);
	}
	for (auto& it : m_gameMap->tile_map_circle)
	{
		m_circleColliderList.push_back(it);
		m_listTriggerAnimation.push_back(it->m_animation);
		//std::cout<< m_listAnimation
	}
	//m_listAnimation.push_back(m_trigger1);
	m_listAnimation.push_back(m_player->m_playerDieEffect);
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
		
		
		/*if (isFalling) {
			jumpBuffer = true;
		}*/
	}

}

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		switch (e.button.button)
		{
		case 1:
			m_KeyPress |= 1 << 4;
			OnButtonPressed = true;
			m_onButtonPressed = true;
			OnButtonDown = true;
			
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
				m_player->m_jumpBuffer = true;
			}


			break;
		}
	}
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
			OnButtonDown = true;
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
				m_player->m_jumpBuffer = true;
			}

			
			break;

		
		default:
			break;
		}

	}
	//Mouse Up
	if (e.type == SDL_MOUSEBUTTONUP)
	{
		switch (e.button.button)
		{
		case 1:
			m_KeyPress ^= 1 << 4;
			OnButtonPressed = false;
			m_onButtonPressed = false;
			m_onButtonUp = true;
			if (std::dynamic_pointer_cast<Ship>(m_player) != NULL && !m_player->m_isFalling) {
				m_player->m_jumpForce = 5000;
			}
			/*m_player->m_isJumping = false;
			m_player->m_isFalling = true;*/
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
			m_onButtonUp = true;
			if (std::dynamic_pointer_cast<Ship>(m_player) != NULL && !m_player->m_isFalling) {
				m_player->m_jumpForce = 5000;
			}
			/*m_player->m_isJumping = false;
			m_player->m_isFalling = true;*/
			break;
			
		default:
			break;
		}

	}
}

void GSPlay::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	if(bIsPressed)
	{
		//std::cout << "sdjkfhdjkfgh";
	}

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
	if(m_player->m_isAlive)
	{
		aliveTime += deltaTime;
	}
	timer += deltaTime;
	
	m_player->Die(aliveTime, 2);
	//std::cout << g_stateControllerPtr;
	try {
		HandleEvents();
		
	m_player->RunIntoScene(m_readyPos, deltaTime);
	m_player->ApplyGravity(m_gravity, deltaTime);
	//std::cout << OnButtonPressed << std::endl;
	m_player->MoveUp(m_gravity, m_onButtonPressed, deltaTime);
	//std::cout << OnButtonPressed << std::endl;
	
	m_player->FixRotationOnGround(deltaTime);
	m_player->Rotate(400.0, deltaTime);
	Map map_data = m_gameMap->getMap();
	m_player->UpdatePlayerPos(deltaTime);
	m_player->UpdatePlayerSprite(m_playerSprite);
	/*for (const auto& collider : m_colliderList) {
		m_player->OnCollisionStay(collider, isFalling);
	}*/
	m_player->UpdatePlayerColliderState();
	

	for (const auto& collider : m_boxColliderList) {
		if (m_player->OnCollisionStay(collider, m_player, m_playerSprite)) {
			m_player->m_isOnGround = true;
			m_player->OnGround();
			if (collider->GetColliderID() == ColliderType::PORTAL_SHIP) {
				std::cout << "changing";
				m_player = m_player->TransformToShip();
			}
			break; // Exit the loop if ground collision is detected with any collider
		}
		else {
			m_player->m_isOnGround = false;
			//m_player->m_isFalling = true;
		}
		

	}
	
	for (const auto& collider : m_circleColliderList) {
		m_player->OnCollisionTrigger(collider, m_gravity, deltaTime);
	}
	
	
	

	
	if (m_player->m_changedState == true) {
		m_player->m_changedState = false;
	}
		if(OnButtonDown == true)
		{
			
			g_trigger = true;
			OnButtonDown = false;
		}
	
	}
	
	catch (std::exception_ptr e) {
		
	}
	//std::cout << m_player->GetPlayerVelocity()<<std::endl;
	std::cout << m_player->GetPlayerRotation()<<std::endl;
	//std::cout << m_player->GetPlayerPosition().x << std::endl;
	//std::cout << m_collider1->GetColliderPosition().y;
	//std::cout << "isFalling " << m_player->m_isFalling << std::endl;
	//std::cout << "isJumping " << m_player->m_isJumping << std::endl;
	//std::cout << "isOnground " << m_player->m_isOnGround << std::endl;
	//std::cout << "direction " << m_player->GetDirectionY() << std::endl;
	//std::cout << "jumpBuffer " << jumpBuffer << std::endl;
	//std::cout << "Number of coliders: " << m_colliderList.size()<<std::endl;
	//std::cout << OnButtonPressed << std::endl;
	//std::cout << m_playerCollider->GetWidth() << std::endl;
	//std::cout << m_player->m_isAlive << std::endl;
	
	

	

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
	if (m_player->m_isAlive == false)
	{
		m_player->m_playerDieEffect->SetPosition(Vector3(m_player->GetPlayerPosition().x - TILE_SIZE / 2, m_player->GetPlayerPosition().y - TILE_SIZE / 2, 0));
		m_player->m_playerDieEffect->SetSize(TILE_SIZE * 2, TILE_SIZE * 2);
			m_player->m_playerDieEffect->Update(deltaTime);
		
	}

	if (m_player->m_isOnGround == true && m_player->m_isAlive)
	{
		canDrawEvent = true;
		m_player->m_playerTrailEffect->SetPosition(Vector3(m_player->GetPlayerPosition().x- TILE_SIZE*1.8 , m_player->GetPlayerPosition().y - TILE_SIZE *1.3, 0));
		m_player->m_playerTrailEffect->SetSize(TILE_SIZE * 3, TILE_SIZE * 3);
		m_player->m_playerTrailEffect->Update(deltaTime);
		m_player->m_playerJumpEffect->SetPosition(Vector3(m_player->GetPlayerPosition().x - TILE_SIZE / 2, m_player->GetPlayerPosition().y - TILE_SIZE / 2, 0));
	}

	if(m_player->m_isJumping == true && canDrawEvent == true)
	{
		
		if (g_trigger == true )
		{
			
			m_player->m_playerJumpEffect->SetSize(TILE_SIZE * 2, TILE_SIZE * 2);
			
			
		}
		m_player->m_playerJumpEffect->Update(deltaTime);
		

	}

	for (auto it : m_listTriggerAnimation)
	{
		it->Update(deltaTime);
	}

	//Process bar
	if (processBarWidth >= PROCESS_WIDTH) {
		currentProcess = currentProcess;
		processBarWidth = PROCESS_WIDTH;
	}
	else {
		currentProcess = ((m_player->GetPlayerPosition().x) / (MAX_MAP_X * TILE_SIZE)) * 100.0f;
		//processBarWidth += ((PROCESS_WIDTH * (PLAYER_SPEED * deltaTime))/ (MAX_MAP_X * TILE_SIZE)) * deltaTime;
		processBarWidth = (m_player->GetPlayerPosition().x) / ((MAX_MAP_X * TILE_SIZE) / PROCESS_WIDTH);
	}
	m_Process->LoadFromRenderText(std::to_string((int)currentProcess) + "%");

	//Save High Process
	if (currentProcess > m_iHighest_process_level_1)
	{
		m_iHighest_process_level_1 = currentProcess;
		m_fileController->WriteToFile("Data/save_data.txt");
	}

	//Moving background
	//m_background = std::get<0>(m_background->MovingBackGround(m_background, m_background_2));
	//m_background_2 = std::get<1>(m_background_2->MovingBackGround(m_background, m_background_2));

	//Update position of camera
	
	Camera::GetInstance()->Update(deltaTime);
	
	
	//std::cout<<Camera::GetInstance()->GetPosition().x;
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
	if(m_player->m_isAlive == false)
	{
		//m_player->m_playerDieEffect->SetCurrentFrame(1);
		
		m_player->m_playerDieEffect->Draw(renderer);
	}
	else
	{
		m_playerSprite->Draw(renderer);
	}
	
	//draw player
	//m_playerSprite->Draw(renderer);
	m_playerCollider->Draw(renderer);
	for (auto it : m_boxColliderList) {
		it->Draw(renderer);
	}

	SDL_Rect foregroundRect = { SCREEN_WIDTH / 2 - 245, PROCESS_PADDING + 20, processBarWidth, PROCESS_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color
	SDL_RenderFillRect(renderer, &foregroundRect);

	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	//obj->Draw(renderer);

	/*for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}*/
	if (!m_circleColliderList.empty()) {
		for (auto it : m_listTriggerAnimation)
		{
			it->Draw(renderer);
		}
	}
	if (m_player->m_isJumping == true && m_player->m_isAlive == true )
	{
		m_player->m_playerJumpEffect->Draw(renderer);
		//canDrawEvent = false;
	}
	if(m_player->m_isOnGround == true && m_player->m_isAlive == true)
	{
		m_player->m_playerTrailEffect->Draw(renderer);
	}
	
	//m_trigger1->Draw(renderer);
	m_slider->DrawFixedObject(renderer);
	m_Process->Draw(renderer);

}