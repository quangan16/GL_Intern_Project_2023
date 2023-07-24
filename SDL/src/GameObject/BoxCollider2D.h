#pragma once
#include <cmath>
#include <Define.h>
#include "Collider2D.h"
#include "Sprite2D.h"

#include <memory>
#include <SDL.h>

#include "CircleCollider2D.h"

class BoxCollider2D : public Collider2D, public Sprite2D {
public:
    // Constructor
    BoxCollider2D();
    BoxCollider2D(Vector2 _objectPos,bool _isActive, float _width, float _height);
	BoxCollider2D(ColliderType _id,Vector2 _objectPos,bool _isActive, float _width, float _height, std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
	



    // Check collision with another box collider
	bool CheckCollision(const std::shared_ptr<BoxCollider2D> &_otherCollider) ;
	bool CheckCollision(const std::shared_ptr<CircleCollider2D> &_otherCollider) ;
    void DrawBoundingBox(SDL_Renderer* renderer, std::shared_ptr<SDL_Color> color) const ;

	void Init() override;
	void Draw(SDL_Renderer* renderer) override;

	void Update(float deltatime) override;
	void Set2DPosition(float x, float y);
	Vector3		Get2DPosition();
	void SetColliderSize(int width, int height);
	void SetSize(int width, int height);
	int GetWidth();
	int GetHeight();
	void SetRotation(double angle);
	void SetFlip(SDL_RendererFlip flip);

protected:
    float m_width;
    float m_height;
};


