#include "BoxCollider2D.h"


BoxCollider2D::BoxCollider2D(Vector2 objectPos, float width, float height) {
    this->m_colliderPosition = objectPos;
    m_width = width;
    m_height = height;
}


bool BoxCollider2D::CheckCollision(Vector2 pos, float width, float height) {
    if (this->m_colliderPosition.x + width / 2 < pos.x - width / 2 || this->m_colliderPosition.x > pos.x + width / 2) return false;
    if (this->m_colliderPosition.y + height < pos.y || this->m_colliderPosition.y > pos.y + height) return false;
    return true;
}


