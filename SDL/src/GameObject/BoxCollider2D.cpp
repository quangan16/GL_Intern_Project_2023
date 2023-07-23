#include "BoxCollider2D.h"
#include "TextureManager.h"



BoxCollider2D::BoxCollider2D(Vector2 objectPos,bool _isActive, float width, float height) {
    this->m_colliderPosition = objectPos;
    this->m_isActive = _isActive;
    m_width = width;
    m_height = height;
}

BoxCollider2D::BoxCollider2D(ColliderType _id,Vector2 _objectPos, bool _isActive, float _width, float _height, std::shared_ptr<TextureManager> _texture, SDL_RendererFlip _flip) 
    : Collider2D(_id,_objectPos, _isActive), Sprite2D(_texture, _flip, _width, _height), m_width{ _width }, m_height { _height } {}

void BoxCollider2D::Init()
{
    // Init Camera
}

void BoxCollider2D::Draw(SDL_Renderer* renderer)
{
    //Get2DPosition();
    if (m_pTexture != nullptr)
    {
        m_pTexture->Render(m_colliderPosition.x, m_colliderPosition.y, m_width, m_height, m_angle, m_flip);
    }

}

void BoxCollider2D::Update(float deltatime)
{
}

void BoxCollider2D::Set2DPosition(float x, float y)
{
    m_position = Vector3((float)x, (float)y, 0.0f);
}

Vector3 BoxCollider2D::Get2DPosition()
{
    return Vector3(m_position.x, m_position.y, 0.0f);
}

void BoxCollider2D::SetSize(int _width, int _height)
{
    m_width = _width;
    m_height = _height;
    m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int BoxCollider2D::GetWidth()
{
    return m_width;
}

int BoxCollider2D::GetHeight()
{
    return m_height;
}

void BoxCollider2D::SetRotation(double angle)
{
    m_angle = angle;
}

void BoxCollider2D::SetFlip(SDL_RendererFlip flip)
{
    m_flip = flip;
}

bool BoxCollider2D::CheckCollision(const std::shared_ptr<BoxCollider2D> &_otherAABBCollider) {
    if (this->m_colliderPosition.x + this->m_width < _otherAABBCollider->m_colliderPosition.x || this->m_colliderPosition.x > _otherAABBCollider->m_colliderPosition.x + _otherAABBCollider->m_width) return false;
    if (this->m_colliderPosition.y + m_height < _otherAABBCollider->m_colliderPosition.y || this->m_colliderPosition.y >  _otherAABBCollider->m_colliderPosition.y + _otherAABBCollider->m_height) return false;
    return true;
}

bool BoxCollider2D::CheckCollision(const std::shared_ptr<CircleCollider2D> &_otherCircleCollider) {
    Vector2 minPoint = m_colliderPosition;
    Vector2 maxPoint = Vector2(m_colliderPosition.x + m_width, m_colliderPosition.y + m_height);
    Vector2 closestPointToCircle = _otherCircleCollider->GetCenterPosition();

    if(closestPointToCircle.x < minPoint.x)
    {
        closestPointToCircle.x = minPoint.x;
    }
    else if(closestPointToCircle.x > maxPoint.x)
    {
        closestPointToCircle.x = maxPoint.x;
    }

    if (closestPointToCircle.y < minPoint.y)
    {
        closestPointToCircle.y = minPoint.y;
    }
    else if (closestPointToCircle.y > maxPoint.y)
    {
        closestPointToCircle.y = maxPoint.y;
    }

    Vector2 minLength = closestPointToCircle - (_otherCircleCollider->GetCenterPosition());
    return minLength.Length() <= _otherCircleCollider->GetRadius();
}



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




