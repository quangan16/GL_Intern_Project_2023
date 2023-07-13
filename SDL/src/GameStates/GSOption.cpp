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

	//sound
	Mix_Music* music = Mix_LoadMUS("");
	if (music == nullptr) {

	}
	Mix_PlayMusic(music, -1);

	//onoffmusic
	//texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
	if (ResourceManagers::GetInstance()->isMuted)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("button_musicoff.tga");
	}
	else
	{
		texture = ResourceManagers::GetInstance()->GetTexture("button_musicon.tga");

	}
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(100, 100);
	button->Set2DPosition(900,540);
	button->SetOnClick([this, texture]() {
		if (!ResourceManagers::GetInstance()->isMuted)
		{
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("button_musicoff.tga"));
			ResourceManagers::GetInstance()->isMuted = true;
		}
		else
		{
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("button_musicon.tga"));
			ResourceManagers::GetInstance()->isMuted = false;
		}
	});
	m_listButton.push_back(button);

	//slider volume
	//volumeBarWidth = (currentVolume * VOLUME_WIDTH) / maxVolume;

	m_KeyPress = 0;
}

void GSOption::updateVolume(int x)
{
	// Calculate the new volume based on the slider position
	volume = (x - SLIDER_PADDING) * 100 / (SCREEN_WIDTH - SLIDER_WIDTH - 2 * SLIDER_PADDING);

	// Clamp the volume between 0 and 100
	if (volume < 0)
		volume = 0;
	else if (volume > 100)
		volume = 100;

	// Set the volume (you can use your own audio API to set the actual volume)
	// SetVolume(volume);
}

void GSOption::Exit()
{

}


void GSOption::Pause()
{

}
void GSOption::Resume()
{

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
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				// Check if the mouse click is within the slider bar
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				if (mouseY >= SCREEN_HEIGHT / 2 - SLIDER_HEIGHT / 2 && mouseY <= SCREEN_HEIGHT / 2 + SLIDER_HEIGHT / 2 &&
					mouseX >= SLIDER_PADDING && mouseX <= SCREEN_WIDTH - SLIDER_WIDTH - SLIDER_PADDING)
				{
					// Update the volume based on the mouse position
					updateVolume(mouseX);
				}
			}
		}
}

void GSOption::Update(float deltaTime)
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
	// Create the background rectangle for the health bar
	//SDL_Rect backgroundRect = { VOLUME_PADDING, VOLUME_PADDING, VOLUME_WIDTH, VOLUME_HEIGHT };
	// Create the foreground rectangle representing the current health
	//SDL_Rect foregroundRect = { VOLUME_PADDING, VOLUME_PADDING, volumeBarWidth, VOLUME_HEIGHT };
	// Set the drawing color to represent the health bar
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
	//SDL_RenderFillRect(renderer, &backgroundRect);
	//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color
	//SDL_RenderFillRect(renderer, &foregroundRect);

	//test
	 // Draw the slider bar background
	SDL_Rect sliderBackgroundRect = { SLIDER_PADDING, SCREEN_HEIGHT / 2 - SLIDER_HEIGHT / 2, SCREEN_WIDTH - 2 * SLIDER_PADDING, SLIDER_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &sliderBackgroundRect);

	// Draw the slider bar
	int sliderPosition = SLIDER_PADDING + (volume * (SCREEN_WIDTH - SLIDER_WIDTH - 2 * SLIDER_PADDING)) / 100;
	SDL_Rect sliderRect = { sliderPosition, SCREEN_HEIGHT / 2 - SLIDER_HEIGHT / 2, SLIDER_WIDTH, SLIDER_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &sliderRect);

	// Update the screen
	SDL_RenderPresent(renderer);
}
