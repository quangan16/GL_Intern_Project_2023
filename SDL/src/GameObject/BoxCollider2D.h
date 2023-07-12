#pragma once
#include <cmath>
#include <Define.h>
#include "Collider2D.h"
#include <memory>
#include <SDL.h>

class BoxCollider2D : public Collider2D {
public:
    // Constructor
    BoxCollider2D();
    BoxCollider2D(Vector2 objectPos, float width, float height);


    // Check collision with another box collider
    bool CheckCollision(const BoxCollider2D& otherCollider) override;
    void DrawBoundingBox(SDL_Renderer* renderer, std::shared_ptr<SDL_Color> color) const ;


protected:
    float m_width;
    float m_height;
};

