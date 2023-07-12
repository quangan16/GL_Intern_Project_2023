#pragma once
#include <cmath>
#include <Define.h>
#include "Collider2D.h"
#include "Sprite2D.h"

#include <memory>
#include <SDL.h>

class BoxCollider2D : public Collider2D, public Sprite2D {
public:
    // Constructor
    BoxCollider2D();
    BoxCollider2D(Vector2 objectPos, float width, float height);
	BoxCollider2D(Vector2 objectPos, float width, float height, std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
	



    // Check collision with another box collider
    bool CheckCollision(const BoxCollider2D& otherCollider) override;
    void DrawBoundingBox(SDL_Renderer* renderer, std::shared_ptr<SDL_Color> color) const ;

	void Init() override;
	void Draw(SDL_Renderer* renderer) override;

	void Update(float deltatime) override;
	void Set2DPosition(float x, float y);
	Vector3		Get2DPosition();
	void SetSize(int width, int height);
	void SetSize();
	int GetWidth();
	int GetHeight();
	void SetRotation(double angle);
	void SetFlip(SDL_RendererFlip flip);

protected:
    float m_width;
    float m_height;
};

