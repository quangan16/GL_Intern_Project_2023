#pragma once
#include "Collider2D.h"
#include "Define.h"
#include "Sprite2D.h"

#include <memory>
class CircleCollider2D : public Collider2D, public Sprite2D{
public:
    // Constructor
    CircleCollider2D(Vector2 objPosition, float radius);

    CircleCollider2D(ColliderType _id, Vector2 _objectPos, bool _isActive, float radius, std::shared_ptr<TextureManager> _texture, SDL_RendererFlip _flip);

    // Check collision with another circle collider
    bool CheckCollision(const CircleCollider2D& otherCircle);

    float GetRadius();
   
private:

    float m_radius;
};

