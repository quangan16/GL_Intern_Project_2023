#pragma once
#include "CMath.h"
#include <memory>

class BoxCollider2D;
class CircleCollider2D;

typedef enum COLLIDER_TYPE {
	PLAYER,
	GROUND,
	OBSTACLE,
	JUMP_BOOST,
	JUMP_BOOST_AUTO,
	GRAVITY_PUSH,
	PORTAL_CUBE,
	PORTAL_SHIP,
	PORTAL_WAVE,
	PORTAL_BALL,
	PORTAL_SPIDER,
	PORTAL_REVERSE,
	FINISH_LINE

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

	Vector2& GetColliderPosition();
	

	void SetColliderPosition(Vector2 _position);
	

	virtual bool CheckCollision(const std::shared_ptr<BoxCollider2D> &_otherCollider) = 0;
	virtual bool CheckCollision(const std::shared_ptr<CircleCollider2D> &_otherCollider) = 0;

	ColliderType GetColliderID() {
		return this->m_colliderID;
	}
};




