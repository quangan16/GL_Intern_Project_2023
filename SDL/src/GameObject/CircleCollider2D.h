#pragma once
#include "Collider2D.h"
#include "Define.h"
class CircleCollider2D : public Collider2D {
public:
    // Constructor
    CircleCollider2D(Vector2 objPosition, float radius);

    // Check collision with another circle collider
    bool CheckCollision(const CircleCollider2D& otherCircle);


private:

    float m_radius;
};

