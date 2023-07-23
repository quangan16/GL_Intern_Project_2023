#include "CircleCollider2D.h"

CircleCollider2D::CircleCollider2D(Vector2 objectPos, float radius) {
    this->m_colliderPosition = objectPos;
    m_radius = radius;
}

CircleCollider2D::CircleCollider2D(ColliderType _id, Vector2 _objectPos, bool _isActive, float _radius, std::shared_ptr<TextureManager> _texture, SDL_RendererFlip _flip)
    : Collider2D(_id, _objectPos, _isActive), m_radius{ _radius }
{
    this->m_centerPosition = Vector2(m_colliderPosition.x + m_radius, m_colliderPosition.y + m_radius);
    m_sprite = std::make_shared<Sprite2D>(_texture, _flip, _radius * 2, _radius * 2);
}


CircleCollider2D::CircleCollider2D(ColliderType _id, Vector2 _objectPos, bool _isActive, float _radius, std::shared_ptr<TextureManager> _texture, int _spriteRow, int _frameCount, int _numAction, float _frameTime, bool _repeatAni)
    : Collider2D(_id, _objectPos, _isActive), SpriteAnimation(_texture,_radius*2, _radius *2, _spriteRow,  _frameCount,   _numAction,  _frameTime, _repeatAni) {
    m_radius = _radius;
    this->m_centerPosition = Vector2(m_colliderPosition.x + m_radius, m_colliderPosition.y + m_radius);
    m_animation = std::make_shared<SpriteAnimation>(_texture, _radius * 2, _radius * 2, _spriteRow, _frameCount, _numAction, _frameTime, _repeatAni);
    m_animation->SetPosition(Vector3{ m_colliderPosition.x, m_colliderPosition.y, 0 });
}

// Check collision with another circle collider
bool CircleCollider2D::CheckCollision(const std::shared_ptr<CircleCollider2D>& otherCircle) {
    float distance = sqrt((this->m_colliderPosition.x - otherCircle->m_colliderPosition.x) * (this->m_colliderPosition.x - otherCircle->m_colliderPosition.x) + (this->m_colliderPosition.y - otherCircle->m_colliderPosition.y) * (this->m_colliderPosition.y - otherCircle->m_colliderPosition.y));
    return distance <= m_radius + otherCircle->m_radius;
}

bool CircleCollider2D::CheckCollision(const std::shared_ptr<BoxCollider2D>& _otherBoxCollider) {
    return false;
}

 float CircleCollider2D::GetRadius() 
{
    return m_radius;
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

 void CircleCollider2D::Init()
 {
     // Init Camera
 }

 Vector2& CircleCollider2D::GetCenterPosition()
{
    return m_centerPosition;
}


 void CircleCollider2D::Draw(SDL_Renderer* renderer)
 {
     
         if (BaseObject::m_pTexture != nullptr)
         {
             BaseObject::m_pTexture->RenderFrame(m_colliderPosition.x, m_colliderPosition.y, SpriteAnimation::m_iWidth, SpriteAnimation::m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, BaseObject::m_angle, BaseObject::m_flip);
         }
     

 }


 void CircleCollider2D::Update(float deltatime)
 {
 }

 void CircleCollider2D::Set2DPosition(float x, float y)
 {
     BaseObject::m_position = Vector3((float)x, (float)y, 0.0f);
 }

 Vector3 CircleCollider2D::Get2DPosition()
 {
     return Vector3(BaseObject::m_position.x, BaseObject::m_position.y, 0.0f);
 }

 void CircleCollider2D::SetSize(int _width, int _height)
 {
     m_radius = _width/2;
     
     BaseObject::m_scale = Vector3((float)SpriteAnimation::m_iWidth, (float)SpriteAnimation::m_iHeight, 0.0f);
 }

 int CircleCollider2D::GetWidth()
 {
     return m_radius*2;
 }

 int CircleCollider2D::GetHeight()
 {
     return m_radius*2;
 }

 void CircleCollider2D::SetRotation(double angle)
 {

     BaseObject::m_angle = angle;
 }

 void CircleCollider2D::SetFlip(SDL_RendererFlip flip)
 {

     BaseObject::m_flip = flip;
 }
