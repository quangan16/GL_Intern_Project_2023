#include "Collider2D.h"


Collider2D::Collider2D() : m_colliderPosition{0.0f, 0.0f}, m_isActive{false}{}

Collider2D::Collider2D(ColliderType _id, Vector2 _position, bool _isActive = true) : m_colliderID{_id}, m_colliderPosition{_position}, m_isActive{_isActive} {}

Vector2 Collider2D::GetColliderPosition()
{
	return this->m_colliderPosition;
}

void Collider2D::SetColliderPosition(Vector2 _position)
{
	this->m_colliderPosition = _position;
}