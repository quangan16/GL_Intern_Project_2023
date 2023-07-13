#pragma once
#include "CMath.h"
#include <memory>

class BoxCollider2D;

typedef enum COLLIDER_TYPE {
	Player,
	GROUND,
	OBSTACLE,
	BOOST,
	GATE
}ColliderType;


class Collider2D
{
protected:
	ColliderType m_colliderID;
	Vector2 m_colliderPosition;
	bool m_isActive;
public:
	Collider2D();
	Collider2D(ColliderType _colliderID,Vector2 _position, bool _isActive);
	virtual ~Collider2D() {}

	Vector2 GetColliderPosition();
	

	void SetColliderPosition(Vector2 _position);
	

	virtual bool CheckCollision(const std::shared_ptr<BoxCollider2D> _otherCollider) = 0;
};




