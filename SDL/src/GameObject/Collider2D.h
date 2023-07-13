#pragma once
#include "CMath.h"

class BoxCollider2D;

class Collider2D
{
protected:
	Vector2 m_colliderPosition;
	bool m_isActive;
public:
	Collider2D() {}
	Collider2D(Vector2 position) {}
	virtual ~Collider2D() {}

	Vector2 GetColliderPosition();
	

	void SetColliderPosition(Vector2 position);
	

	virtual bool CheckCollision(const BoxCollider2D& otherCollider) = 0;
};

