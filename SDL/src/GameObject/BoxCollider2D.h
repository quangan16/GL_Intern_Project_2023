#pragma once
#include <cmath>
#include <Define.h>
#include "Collider2D.h"

class BoxCollider2D : public Collider2D {
public:
    // Constructor
    BoxCollider2D();
    BoxCollider2D(Vector2 objectPos, float width, float height);


    // Check collision with another box collider
    bool CheckCollision(Vector2 pos, float width, float height) override;


protected:
    float m_width;
    float m_height;
};

