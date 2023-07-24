#pragma once
#include "CMath.h"
#include "SDL.h"
#include "Sprite2D.h"
#include "Define.h"
#include "Player.h"
#include "GameManager/Singleton.h"
class Camera : public CSingleton<Camera>
{
public:
	Camera() { m_ViewBox = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; }
	void InitPosition();
	SDL_Rect GetViewBox();
	Vector2 GetPosition();
	void SetTarget(std::shared_ptr<Sprite2D> target);
	void Update(float deltaTime);
	void UpdateOnYAxis(float _deltaTime);
	//void Update2(std::shared_ptr<Player>& _player, float deltaTime);
	void SetPosition(Vector2 _position);
private:
	std::shared_ptr<Sprite2D> m_Target;
	Vector2 m_Position;
	SDL_Rect m_ViewBox;
	float m_Smooth = 5.0f;

	bool hasGetLocationY = false;
	Vector2 newCameraPosition;
};