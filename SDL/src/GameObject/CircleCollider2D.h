#pragma once
#include "Collider2D.h"
#include "Define.h"
#include "Sprite2D.h"
#include "BoxCollider2D.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"
#include "BaseObject.h"

#include <memory>
class CircleCollider2D : public Collider2D  , virtual public SpriteAnimation{
public:
    // Constructor
    CircleCollider2D(Vector2 objPosition, float radius);

    //CircleCollider2D(ColliderType _id, Vector2 _objectPos, bool _isActive, float radius, std::shared_ptr<TextureManager> _texture, SDL_RendererFlip _flip);

    CircleCollider2D(ColliderType _id, Vector2 _objectPos, bool _isActive, float radius, std::shared_ptr<TextureManager> _texture, int _spriteRow, int _frameCount, int _numAction, float _frameTime, bool _repeatAni = true);

    // Check collision with another circle collider
    bool CheckCollision(const std::shared_ptr<CircleCollider2D>& otherCircle)override;
	bool CheckCollision(const std::shared_ptr<BoxCollider2D>& _otherCollider) override;

    float GetRadius();


	void Init() override;
	void Draw(SDL_Renderer* renderer) override;

	void Update(float deltatime) override;
	void Set2DPosition(float x, float y);
	Vector3		Get2DPosition();
	void SetSize(int width, int height);
	void SetSize();
	int GetWidth();
	int GetHeight();
	void SetRotation(double angle);
	void SetFlip(SDL_RendererFlip flip);

	std::shared_ptr<SpriteAnimation> m_animation;

private:
   
    float m_radius;
};

