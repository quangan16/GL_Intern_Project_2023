#include "BoxCollider2D.h"



BoxCollider2D::BoxCollider2D(Vector2 objectPos, float width, float height) {
    this->m_colliderPosition = objectPos;
    m_width = width;
    m_height = height;
}


bool BoxCollider2D::CheckCollision(const BoxCollider2D &otherCollider) {
    if (this->m_colliderPosition.x + this->m_width < otherCollider.m_colliderPosition.x || this->m_colliderPosition.x > otherCollider.m_colliderPosition.x+otherCollider.m_width) return false;
    if (this->m_colliderPosition.y + m_height < otherCollider.m_colliderPosition.y || this->m_colliderPosition.y >  otherCollider.m_colliderPosition.y + otherCollider.m_width) return false;
    return true;
}

//~Above code equivalent to
//bool BoxCollider2D::CheckCollision(const BoxCollider2D& otherCollider) {
//    return !(this->m_colliderPosition.x + this->m_width < otherCollider.m_colliderPosition.x ||
//        this->m_colliderPosition.x > otherCollider.m_colliderPosition.x + otherCollider.m_width ||
//        this->m_colliderPosition.y + this->m_height < otherCollider.m_colliderPosition.y ||
//        this->m_colliderPosition.y > otherCollider.m_colliderPosition.y + otherCollider.m_height);
//}

void BoxCollider2D::DrawBoundingBox(SDL_Renderer* renderer, std::shared_ptr<SDL_Color> color) const {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

    int left = m_colliderPosition.x - m_width;
    int right = m_colliderPosition.x + m_width;
    int top = m_colliderPosition.y;
    int bottom = m_colliderPosition.y + m_height;

    SDL_RenderDrawLine(renderer, left, top, right, top);
    SDL_RenderDrawLine(renderer, right, top, right, bottom);
    SDL_RenderDrawLine(renderer, right, bottom, left, bottom);
    SDL_RenderDrawLine(renderer, left, bottom, left, top);
}


