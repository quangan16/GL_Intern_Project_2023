#include <stdio.h>
#include <string>
#include "Game.h"
#include "GameStateBase.h"
#include "GameStateMachine.h"
//Screen dimension constants
#include"SDL_mixer.h"
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
Game::Game()
{
	//Init create window for rendering
	Init();
}
bool Game::Init()
{
	bool success=	Renderer::GetInstance()->Init();
	GameStateMachine::GetInstance()->PushState(StateType::STATE_INTRO);
	return success;
}

void Game::Run()
{

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			//Current animation frame
			int frame = 0;
			
			//Angle of rotation
			double degrees = 0;

			int scrollingOffset = 0;
			//Flip type
			SDL_RendererFlip flipType = SDL_FLIP_NONE;
			TextureManager* currentTexure= NULL;
			//Uint32 startTime = 0;
			std::string textTime;
			//Start counting frames per second
			Uint32 start = SDL_GetTicks();
			//int countedFrames = 0;
		//	fpsTimer->Start();
			//While application is runningkaka
			capTimer = std::make_shared<Timer>();
			Uint32 startTime = SDL_GetTicks();

			double deltaTime = 0;
			Uint32 lastUpdate = SDL_GetTicks();
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{

					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					if (GameStateMachine::GetInstance()->HasState())
					{
						GameStateMachine::GetInstance()->CurrentState()->HandleKeyEvents(e);
					}

					//Handle Touch Event
					if (GameStateMachine::GetInstance()->HasState())
					{
						GameStateMachine::GetInstance()->CurrentState()->HandleTouchEvents(e, true);
					}

				}
				//Clear screen
				SDL_SetRenderDrawColor(Renderer::GetInstance()->GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Renderer::GetInstance()->GetRenderer());
				//Render
				/*Uint32 end = SDL_GetTicks();
				float deltaTime = end - start;
				start = end;*/

				//Calculate time step
				float timeStep = capTimer->GetTicks() / 1000.f;
				//float deltaTime = (SDL_GetTicks() - startTime) / 1000.0f;
				//float deltaTime = (SDL_GetTicks() - m_LastTime) * (60 / 1000.0f);
				Uint32 current = SDL_GetTicks();


				float dT = (current - lastUpdate) / 1000.0f;
				// Set updated time
				lastUpdate = current;
				//printf("Hoa deltaTime = %f", deltaTime);
				Update(dT);

				//Restart step timer
				capTimer->Start();

				////Limit FPS
				Uint32 targetTime = 1000 / 60;
				if (dT < targetTime)
				{
					SDL_Delay(targetTime - deltaTime);
				}
				//Update screen
				SDL_RenderPresent(Renderer::GetInstance()->GetRenderer());
			}
}

void Game::Update(float deltaTime)
{
	GameStateMachine::GetInstance()->PerformStateChange();
	if (GameStateMachine::GetInstance()->HasState())
	{
		GameStateMachine::GetInstance()->CurrentState()->Update(deltaTime);
		
		GameStateMachine::GetInstance()->CurrentState()->Draw(Renderer::GetInstance()->GetRenderer());
	}
}


Game::~Game()
{
	Renderer::GetInstance()->FreeInstance();
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

