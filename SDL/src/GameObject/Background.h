#pragma once
#include"Sprite2D.h"

class Background : public Sprite2D
{
protected:
	float m_fBackground_speed;
public:
	Background() : Sprite2D(), m_fBackground_speed(0.0f) {}
	Background(std::shared_ptr<TextureManager> texture, float m_fBackground_speed, SDL_RendererFlip flip);
	void Init() override;
	void Draw(SDL_Renderer* renderer) override;
	void Update(float deltatime) override;
	void SetSpeed(float speed);
	float GetSpeed();
	void Set2DPosition(float x, float y);
	Vector3 Get2DPosition();
	void SetSize(int width, int height);
	int GetWidth();
	int GetHeight();

	void SetRotation(double angle);
	void SetFlip(SDL_RendererFlip flip);
	void GetPositionOnMouseClick();

	std::tuple<std::shared_ptr<Background>, std::shared_ptr<Background>> MovingBackGround(std::shared_ptr<Background> bg1, std::shared_ptr<Background> bg2);
};