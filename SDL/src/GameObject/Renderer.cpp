#include"Renderer.h"
#include "Define.h"
Renderer::Renderer()
{
	WALKING_ANIMATION_FRAMES = 4;
	gWindow = NULL;
	gRenderer = NULL;
	gFont = NULL;
	for (int i = 0; i < 4; i++)
	{
		gSpriteClips[i] = new SDL_Rect[4];
	}
	}
	
Renderer::~Renderer()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
}
bool Renderer::Init()
{
	//Initialization flag
	bool success = true;

	////Initializeo SDL
	//if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) //SDL_INIT_AUDIO for Init SDL audio
	//{
	//	printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	//	success = false;
	//}
	//else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIDHT, SDL_WINDOW_SHOWN);
		//Renderer::GetInstance()->SetWindow(gWindow);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			//Renderer::GetInstance()->SetRenderer(gRenderer);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(Renderer::GetInstance()->GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

				////Initialize PNG loading
				//int imgFlags = IMG_INIT_PNG;
				//if (!(IMG_Init(imgFlags) & imgFlags))
				//{
				//	printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				//	success = false;
				//}

				//Initialize SDL_mixer
				// first argument sets the sound frequency, and 44100 is a standard frequency that works on most systems. The second argument determines the sample format, which again here we're using the default. The third argument is the number of hardware channels, and here we're using 2 channels for stereo. The last argument is the sample size, which determines the size of the chunks we use when playing sound. 2048 bytes (AKA 2 kilobyes) worked fine for me, but you may have to experiment with this value to minimize lag when playing sounds.
			/*	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}*/

				////Initialize SDL_ttf
				//if (TTF_Init() == -1)
				//{
				//	printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				//}
			}
		}
	}
	
	return success;
}
SDL_Window* Renderer::GetWindow()
{
	return gWindow;
}
SDL_Renderer* Renderer::GetRenderer()
{
	return gRenderer;
}
void Renderer::SetWindow(SDL_Window* mWindow)
{
	gWindow = mWindow;
}

void Renderer::SetRenderer(SDL_Renderer* mRenderer)
{
	gRenderer = mRenderer;
}

//void Renderer::SetTTFFont(TTF_Font* mFont)
//{
//	gFont = mFont;
//}

//TTF_Font* Renderer::GetFont()
//{
//	return gFont;
//}

SDL_Rect* Renderer::GetSpriteClips()
{
	for (int i = 0; i < 4; i++)
	{
		return gSpriteClips[i];
	}
	return nullptr;
}


void Renderer::SetSpriteClips(SDL_Rect** mSpriteClips)
{
	for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++)
	{
		gSpriteClips[i] = mSpriteClips[i];
	}
}
