#include "GSPlay.h"


#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "GameObject/Background.h"
#include "GameObject/GameMap.h"

GSPlay::GSPlay():GameStateBase(StateType::STATE_PLAY)
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	index_color = 0;
	isWin = false;
	if(g_stateControllerPtr->GetGameStateType() == StateType::STATE_PLAY)
	{
		/*delete g_stateControllerPtr;
		g_stateControllerPtr = nullptr;*/
	}
	
	//Map
	victoryTime = 0.0f;
	//Map
	m_gameMap = std::make_shared<GameMap>();
	m_gameMap->LoadMap("Data/GP_Level_" + std::to_string(m_iMapTexture_index) + ".csv");
	m_gameMap->DrawMap();

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
	canDrawEvent = true;
	timer = 0.0f;
	aliveTime = 0.0f;
	m_savePoint = std::make_shared<SavePoint>();

	m_savePointMode = false;
	m_immortalMode = false;
	
	auto texture = ResourceManagers::GetInstance()->GetTexture("backx2.tga");
	texture->setColor(map_color[m_iMapTexture_index-1][index_color].r, map_color[m_iMapTexture_index-1][index_color].g , map_color[m_iMapTexture_index-1][index_color].b);
	texture->SetAlpha(255-75);
	if (!isMuted)
	{
		m_Sound = std::make_shared<Sound>("Data/Sounds/map_" + (std::to_string(m_iMapTexture_index)) + ".mp3");
		m_playerDieSfx = std::make_shared<Sound>("Data/Sounds/DeadSoundSfx.mp3");
	}
	// background_1
	m_background1 = std::make_shared<Background>(texture, 2.0f, SDL_FLIP_NONE);
	m_background1->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT * 2);
	m_background1->Set2DPosition(0, 0);
	m_listBackground.push_back(m_background1);

	// background_2
	m_background2 = std::make_shared<Background>(texture, 2.0f, SDL_FLIP_NONE);
	m_background2->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT * 2);
	m_background2->Set2DPosition(SCREEN_WIDTH, 0);
	m_listBackground.push_back(m_background2);
	m_color = std::make_shared<SDL_Color>();

	
	//Test jump trigger
	/*{

		texture = ResourceManagers::GetInstance()->GetTexture("circleBorder.tga");
		m_trigger1 = std::make_shared<CircleCollider2D>(ColliderType::JUMP_BOOST, Vector2(1200, 500), true, TILE_SIZE, texture, SDL_FLIP_NONE);
		m_trigger1->SetFlip(SDL_FLIP_HORIZONTAL);
		m_trigger1->SetSize(90, 90);
		m_trigger1->Set2DPosition(640, 800);
	}*/
	texture = ResourceManagers::GetInstance()->GetTexture("player_cube_" + std::to_string(m_iCharacterTexture_index) + ".tga");
	m_player = std::make_shared<Cube>(Vector2(0.0f, 1400.0f), 0.0, 1, 0.0, texture, SDL_FLIP_NONE, TILE_SIZE, TILE_SIZE);
	m_playerCollider = m_player->GetCollider();
	m_playerCollider->SetColliderSize(TILE_SIZE, TILE_SIZE);
	m_player->m_changedState = false;
	Camera::GetInstance()->SetTarget(m_player);
	// button close
	/*texture = ResourceManagers::GetInstance()->GetTexture("button_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		g_stateControllerPtr.reset();
		g_stateControllerPtr = nullptr;
		

		});
	m_listButton.push_back(button);*/

	texture = ResourceManagers::GetInstance()->GetTexture("Pratice_Button_Off.png");
	m_practiceButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_practiceButton->SetSize(100, 100);
	m_practiceButton->Set2DPosition(30, 10);
	m_practiceButton->SetOnClick([this, texture]() {
		OnButtonPressed = false;
		m_savePointMode = true;
		
		});

	texture = ResourceManagers::GetInstance()->GetTexture("Pratice_Button.png");
	m_practiceButtonOff = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_practiceButtonOff->SetSize(100, 100);
	m_practiceButtonOff->Set2DPosition(30, 10);
	m_practiceButtonOff->SetOnClick([this, texture]() {
		OnButtonPressed = false;
		m_savePointMode = false;

		});


	texture = ResourceManagers::GetInstance()->GetTexture("Immortal_Button_Off.png");
	m_immortalButtonOff = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_immortalButtonOff->SetSize(100, 100);
	m_immortalButtonOff->Set2DPosition(150, 10);
	m_immortalButtonOff->SetOnClick([this, texture]() {
		OnButtonPressed = false;
		m_immortalMode = true;
		});
	texture = ResourceManagers::GetInstance()->GetTexture("Immortal_Button_On.png");
	m_immortalButtonOn = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_immortalButtonOn->SetSize(100, 100);
	m_immortalButtonOn->Set2DPosition(150, 10);
	m_immortalButtonOn->SetOnClick([this, texture]() {
		OnButtonPressed = false;
		m_immortalMode = false;
		});
	
	// panel
	/*texture = ResourceManagers::GetInstance()->GetTexture("panel.tga");
	auto m_panel = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_panel->SetSize(1920 / 3, 1080 / 3);
	m_panel->Set2DPosition((SCREEN_WIDTH - m_panel->GetWidth()) / 2, (SCREEN_HEIGHT - m_panel->GetHeight()) / 2);
	m_panel->SetOnClick([this]() {
		});
	m_listPauseButton.push_back(m_panel);*/
	// button pause;
	texture = ResourceManagers::GetInstance()->GetTexture("button_pause2.tga");
	m_pauseButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_pauseButton->SetSize(100, 100);
	m_pauseButton->Set2DPosition(SCREEN_WIDTH - m_pauseButton->GetWidth() - 10, 10);
	m_pauseButton->SetOnClick([this]() {
			OnButtonPressed = false;
			isPause = !isPause;
		});
	m_listButton.push_back(m_pauseButton);
	
	// button restart
	texture = ResourceManagers::GetInstance()->GetTexture("button_pause2.tga");
	

	// pause window
	texture = ResourceManagers::GetInstance()->GetTexture("button_play1.tga");
	m_resumeButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_resumeButton->SetSize(100, 100);
	m_resumeButton->Set2DPosition((SCREEN_WIDTH - m_resumeButton->GetWidth()) / 2,
		(SCREEN_HEIGHT - m_resumeButton->GetHeight()) / 2);
	m_resumeButton->SetOnClick([this]()
		{
			if (isPause)
			{
				isPause = !isPause;
			}
		});
	m_listPauseButton.push_back(m_resumeButton);
	
	//menu button
	texture = ResourceManagers::GetInstance()->GetTexture("Menu.tga");
	auto m_menuButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_menuButton->SetSize(100, 100);
	m_menuButton->Set2DPosition((SCREEN_WIDTH - m_resumeButton->GetWidth()) / 2 + m_resumeButton->GetWidth() + 30,
		(SCREEN_HEIGHT - m_menuButton->GetHeight()) / 2);
	m_menuButton->SetOnClick([this]()
		{
			if (isPause)
			{
				GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
				g_stateControllerPtr.reset();
				g_stateControllerPtr = nullptr;
			}
		});
	m_listPauseButton.push_back(m_menuButton);
	if (!isMuted) m_Sound->PlaySound();

	// replay button
	texture = ResourceManagers::GetInstance()->GetTexture("Replay.tga");
	auto m_replayButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_replayButton->SetSize(100, 100);
	m_replayButton->Set2DPosition((SCREEN_WIDTH - m_resumeButton->GetWidth()) / 2 - m_replayButton->GetWidth() - 30,
		(SCREEN_HEIGHT - m_menuButton->GetHeight()) / 2);
	m_replayButton->SetOnClick([this]()
		{
			if (isPause)
			{
				GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
			}
		});
	m_listPauseButton.push_back(m_replayButton);

	

	//Slider
	texture = ResourceManagers::GetInstance()->GetTexture("slider.tga");
	m_slider = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_slider->SetSize(500, 20);
	m_slider->Set2DPosition(SCREEN_WIDTH / 2 - 250, 20);

	//Process
	SDL_Color text_Color = { 255, 255, 255 };
	m_Process = std::make_shared<Text>("Data/PUSAB___.otf", text_Color);
	m_Process->SetSize(70, 50);
	m_Process->Set2DPosition(m_slider->Get2DPosition().x + m_slider->GetWidth() + 10, 10);
	m_Process->LoadFromRenderText(std::to_string(currentProcess));

	//Init Player
	//Cube
	//std::cout << m_iCharacterTexture_index << std::endl;
	

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


	m_savePoint->PushSavePoint(m_player);
	//Test Colliders
	/*texture = ResourceManagers::GetInstance()->GetTexture("collider_border.tga");
	m_collider1 = std::make_shared<BoxCollider2D>(ColliderType::GROUND, Vector2(0.0f, 500.0f), true, 5000.0f, 410.0f, texture, SDL_FLIP_NONE);
	m_collider2 = std::make_shared<BoxCollider2D>(ColliderType::GROUND, Vector2(5100.0f, 500.0f), true, 5000.0f, 410.0f, texture, SDL_FLIP_NONE);
	m_colliderList.push_back(m_collider2);
	m_colliderList.push_back(m_collider1);*/
	/*m_savePoint->PushSavePoint(m_player);*/

	Camera::GetInstance()->InitPosition();

	//Dummy ground
	//m_ground = std::make_shared<Player>(Vector2(0.0f, 400.0f), 480.0f, 210.0f);

	
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
	if (!isPause)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
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
	}
	//If a key was pressed
	if (e.type == SDL_KEYDOWN)
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
		case SDLK_ESCAPE:
			isPause = !isPause;
			break;
		case SDLK_x:
			if(m_savePoint->m_savePointStack.size()>1)
			{
				m_savePoint->PopSavePoint();
			}else
			{
				std::cout << "can't pop more";
			}
			
			break;
		case SDLK_SPACE:
			m_KeyPress |= 1 << 4;
			OnButtonPressed = true;
			m_onButtonDown = true;
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
	if (!isPause)
	{
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			switch (e.button.button)
			{
			case 1:
				m_KeyPress ^= 1 << 4;
				OnButtonPressed = false;
				m_onButtonPressed = false;
				m_onButtonUp = true;
				m_player->m_isOnTop == false;

				if (std::dynamic_pointer_cast<Ship>(m_player) != NULL && !m_player->m_isFalling) {
					m_player->m_jumpForce = 5000;
				}
				/*m_player->m_isJumping = false;
				m_player->m_isFalling = true;*/
				break;
			}
		}
	}
	////Key Up
	if (e.type == SDL_KEYUP)
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
			m_onButtonDown = false;
			m_onButtonUp = true;
			m_player->m_isOnTop == false;
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
	if (bIsPressed)
	{
		//std::cout << "sdjkfhdjkfgh";
	}
	if(!m_savePointMode)
	{
		m_practiceButton->HandleTouchEvent(&e);
	}
	else
	{
		m_practiceButtonOff->HandleTouchEvent(&e);
	}

	if (!m_immortalMode)
	{
		m_immortalButtonOff->HandleTouchEvent(&e);
	}
	else
	{
		m_immortalButtonOn->HandleTouchEvent(&e);
	}
	

	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}

	for (auto button : m_listPauseButton)
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
	
	//background moving
	timer += deltaTime;
	
	if (m_player->m_isAlive && !isPause)
	{
	
		aliveTime = timer;
		m_background1->MovingBackGround(m_background2);
		
	}
	if(!m_player->m_hasWon)
	{
		victoryTime = timer;
	}
	

	
	if (!isPause)
	{
		//std::cout << g_stateControllerPtr;
		try {
			
			HandleEvents();
			
			if (m_player->m_isAlive)
			{

				m_savePoint->PushSavePointOverTime(m_player);
			}
			//m_player->RunIntoScene(m_readyPos, deltaTime);
			
			//std::cout << OnButtonPressed << std::endl;
			m_player->MoveUp(m_gravity, m_onButtonPressed, deltaTime);
			//std::cout << OnButtonPressed << std::endl;

			m_player->FixRotationOnGround(deltaTime);
			m_player->Rotate(390.0, deltaTime);
			m_player->UpdatePlayerPos(deltaTime);
			if(m_player->GetPlayerSprite() != nullptr)
			{
				m_player->UpdatePlayerSprite();

			}else if(m_player->GetPlayerAnimation())
			{
				m_player->UpdatePlayerAnimation();
			}
			
			/*for (const auto& collider : m_colliderList) {
				m_player->OnCollisionStay(collider, isFalling);
			}*/
			m_player->UpdatePlayerColliderState();
			m_player->ApplyGravity(m_gravity, deltaTime);
			
			for (const auto& collider : m_boxColliderList) {
				if (m_player->OnCollisionStay(collider, m_player, m_gameMap, m_background1, m_background2)) {
					m_player->m_isOnGround = true;
					m_player->OnGround();
					
					break; // Exit the loop if ground collision is detected with any collider
				}
				else {
					m_player->m_isOnGround = false;
					m_player->m_isFalling = true;
				}
				


			}
			
			m_player->Die(m_savePoint, m_background1, m_Sound, m_playerDieSfx, m_gameMap, aliveTime, 2);
			m_player->UpdatePlayerForm(m_player);
			m_player->Victory(victoryTime, 3);

			for (const auto& collider : m_circleColliderList) {
				m_player->OnCollisionTrigger(collider, m_gravity, deltaTime);
			}


			


			
			if (OnButtonDown == true)
			{

				g_trigger = true;
				OnButtonDown = false;
			}

		}

		catch (std::exception_ptr e) {

		}
		//std::cout << m_player->GetPlayerVelocity()<<std::endl;
		//std::cout << m_player->GetPlayerRotation() << std::endl;
		//std::cout << m_player->GetPlayerPosition().x << std::endl;
		//std::cout << m_playerCollider->GetColliderPosition().x<<std::endl;
		//std::cout << "isFalling " << m_player->m_isFalling << std::endl;
		//std::cout << "isJumping " << m_player->m_isJumping << std::endl;
		//std::cout << "isOnground " << m_player->m_isOnGround << std::endl;
		std::cout << "isOnTop " << m_player->m_isOnTop << std::endl;

		//std::cout << "direction " << m_player->GetDirectionY() << std::endl;
		//std::cout << "jumpBuffer " << jumpBuffer << std::endl;
		//std::cout << "Number of coliders: " << m_colliderList.size()<<std::endl;
		//std::cout << OnButtonPressed << std::endl;
		//std::cout << m_playerCollider->GetWidth() << std::endl;
		//std::cout << m_player->m_isAlive << std::endl;
		//std::cout << m_player->GetPlayerForm() << std::endl;
		//std::cout << m_immortalMode << std::endl;
		//std::cout << m_savePointMode << std::endl;
		std::cout << m_onButtonPressed << std::endl;

		


		

		
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
		
			m_practiceButton->Update(deltaTime);
		
		
			m_practiceButtonOff->Update(deltaTime);
			m_immortalButtonOn->Update(deltaTime);
			m_immortalButtonOff->Update(deltaTime);
		
		

		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}

		for (auto it : m_listPauseButton)
		{
			it->Update(deltaTime);
		}
		for (auto it : m_listBackground)
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
			m_player->m_playerTrailEffect->SetPosition(Vector3(m_playerCollider->GetColliderPosition().x - m_playerCollider->GetWidth() * 2, m_playerCollider->GetColliderPosition().y - m_playerCollider->GetHeight() * 1.3  , 0));
			m_player->m_playerTrailEffect->SetSize(TILE_SIZE * 3, TILE_SIZE * 3);
			m_player->m_playerTrailEffect->Update(deltaTime);
			m_player->m_playerJumpEffect->SetPosition(Vector3(m_player->GetPlayerPosition().x - TILE_SIZE / 2, m_player->GetPlayerPosition().y - TILE_SIZE / 2, 0));
		}


		if (m_player->m_isJumping == true && canDrawEvent == true)
		{

			if (g_trigger == true)
			{

				m_player->m_playerJumpEffect->SetSize(TILE_SIZE * 2, TILE_SIZE * 2);


			}
			m_player->m_playerJumpEffect->Update(deltaTime);


		}
		if(m_player->GetPlayerAnimation() != NULL)
		{
			m_player->GetPlayerAnimation()->Update(deltaTime);
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
		if (currentProcess > m_Highscore[m_iMapTexture_index-1])
		{
			m_Highscore[m_iMapTexture_index-1] = currentProcess;
			m_fileController->WriteToFile("Data/save_data.txt");
		}
		/*if (isWin)
		{
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_WIN);
		}*/

		//Moving background
		//m_background = std::get<0>(m_background->MovingBackGround(m_background, m_background_2));
		//m_background_2 = std::get<1>(m_background_2->MovingBackGround(m_background, m_background_2));

	//Update position of camera
		Camera::GetInstance()->UpdateOnYAxis(deltaTime);
		Camera::GetInstance()->Update(deltaTime);


		//std::cout<<Camera::GetInstance()->GetPosition().x;
		/*obj->update(deltatime);*/
		//printf("%f, \n", obj->GetPosition().x);
		//std::system("cls");
	}
	
		m_player->m_changedState = false;
	
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	for (auto it : m_listBackground)
	{
		it->Draw(renderer);
	}

	//m_score->Draw(renderer);
	

	

	//draw player
	//m_playerSprite->Draw(renderer);
	for (auto it : m_gameMap->noneColliderObjectList)
	{
		it->Draw(renderer);
	}
	
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

	if (isPause)
	{
		for (auto it : m_listPauseButton)
		{
			it->Draw(renderer);
		}
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
	if (m_player->m_isJumping == true && m_player->m_isAlive == true)
	{
		m_player->m_playerJumpEffect->Draw(renderer);
		//canDrawEvent = false;
	}
	if (m_player->m_isOnGround == true && m_player->m_isAlive == true)
	{
		m_player->m_playerTrailEffect->Draw(renderer);
	}

	if (m_player->GetPlayerAnimation() != NULL && m_player->m_isAlive)
	{
		m_player->GetPlayerAnimation()->Draw(renderer);
	}

	if (m_savePointMode == true)
	{
		m_practiceButton->Draw(renderer);
	}
	else if(m_savePointMode == false)
	{
		m_practiceButtonOff->Draw(renderer);
	}

	if (m_immortalMode == true)
	{
		m_immortalButtonOn->Draw(renderer);
	}
	else if (m_immortalMode == false)
	{
		m_immortalButtonOff->Draw(renderer);
	}

	//m_trigger1->Draw(renderer);
	m_slider->DrawFixedObject(renderer);
	m_Process->Draw(renderer);
	if (m_player->m_isAlive == false)
	{
		//m_player->m_playerDieEffect->SetCurrentFrame(1);

		m_player->m_playerDieEffect->Draw(renderer);
	}
	else
	{
		if (m_player->GetPlayerSprite() != NULL)
		{
			m_player->GetPlayerSprite()->Draw(renderer);
		}

	}

}