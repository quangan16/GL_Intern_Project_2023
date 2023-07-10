#include "CircleCollider2D.h"




CircleCollider2D::CircleCollider2D(Vector2 objectPos, float radius) {
    this->m_colliderPosition = objectPos;
    m_radius = radius;
}

// Check collision with another circle collider
bool CircleCollider2D::CheckCollision(const CircleCollider2D& otherCircle) {
    float distance = sqrt((this->m_colliderPosition.x - otherCircle.m_colliderPosition.x) * (this->m_colliderPosition.x - otherCircle.m_colliderPosition.x) + (this->m_colliderPosition.y - otherCircle.m_colliderPosition.y) * (this->m_colliderPosition.y - otherCircle.m_colliderPosition.y));
    return distance <= m_radius + otherCircle.m_radius;
}

//bool CircleCollider2D::CheckCollision(Circle circle, Square square) {
//    // Find the closest point on the square to the center of the circle
//    float closestX = std::max(square.x - square.side / 2.0f, std::min(circle.x, square.x + square.side / 2.0f));
//    float closestY = std::max(square.y - square.side / 2.0f, std::min(circle.y, square.y + square.side / 2.0f));
//
//    // Calculate the distance between the closest point and the center of the circle
//    float distanceX = closestX - circle.x;
//    float distanceY = closestY - circle.y;
//    float distanceSquared = distanceX * distanceX + distanceY * distanceY;
//
//    // Check if the distance is less than or equal to the radius of the circle
//    return distanceSquared <= circle.radius * circle.radius;
//}