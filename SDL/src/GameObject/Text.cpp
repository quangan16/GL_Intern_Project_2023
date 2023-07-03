#include"Text.h"
Text::Text(std::string fontPath, SDL_Color textColor)
	: m_TextColor(textColor)
{
	//Initialize font
	m_Font = TTF_OpenFont(fontPath.c_str(), 28);

	if (m_Font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		return;
	}
	m_pTexture = std::make_shared<TextureManager>();
	//m_TextureText = textureText;
	//m_TextColor = textColor;
	m_position = Vector3(-1.0f, 1.0f, 1.0f);
	
	
}
void Text::LoadFromRenderText(std::string textureText)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->LoadFromRendererText(m_Font , textureText, m_TextColor);
	}
}

void Text::Init()
{
}

void Text::Draw(SDL_Renderer* renderer)
{
	m_pTexture->Render(m_position.x, m_position.y, m_iWidth, m_iHeight);
}

void Text::Update(float deltatime)
{
}


