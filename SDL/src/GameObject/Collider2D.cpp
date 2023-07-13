#include "Collider2D.h"


Vector2 Collider2D::GetColliderPosition()
{
	return this->m_colliderPosition;
}

void Collider2D::SetColliderPosition(Vector2 position)
{
	this->m_colliderPosition = position;
}