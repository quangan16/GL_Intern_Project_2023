#pragma once
#include "CMath.h"
#include <memory>

class BoxCollider2D;

class Collider2D
{
protected:
	Vector2 m_colliderPosition;
	bool m_isActive;
public:
	Collider2D();
	Collider2D(Vector2 position, bool _isActive);
	virtual ~Collider2D() {}

	Vector2 GetColliderPosition();
	

	void SetColliderPosition(Vector2 position);
	

	virtual bool CheckCollision(const std::shared_ptr<BoxCollider2D> _otherCollider) = 0;
};

