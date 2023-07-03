#include "Dot.h"
#include"Define.h"
Dot::Dot(int x, int y)
{
	mPosX = x;
	mPosY = y;

	mVelX = 0;
	mVelY = 0;
	mCollider.r = DOT_WIDTH / 2;
	ShiftColliders();
}
Dot::~Dot()
{

}
void Dot::HandleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			mVelY -= DOT_VEL;
			break;
		case SDLK_DOWN:
			mVelY += DOT_VEL;
			break;
		case SDLK_LEFT:
			mVelX -= DOT_VEL;
			break;
		case SDLK_RIGHT:
			mVelX += DOT_VEL;
			break;
		default:
			break;
		}

	}
	////If a key was pressed
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			mVelY += DOT_VEL;
			break;
		case SDLK_DOWN:
			mVelY -= DOT_VEL;
			break;
		case SDLK_LEFT:
			mVelX += DOT_VEL;
			break;
		case SDLK_RIGHT:
			mVelX -= DOT_VEL;
			break;
		default:
			break;
		}

	}
}
void Dot::Move()
{
	//Move the dot left or right
	mPosX += mVelX ;
	//If the dot went too far to the left or right
	if (mPosX < 0 || mPosX + DOT_WIDTH > SCREEN_WIDTH)
	{
		mPosX -= mVelX ;
	}

	//Move the dot up or Down
	mPosY += mVelY;
	//If the dot went too far to the up or down
	if (mPosY< 0 || mPosY + DOT_HEIGHT > SCREEN_HEIDHT)
	{
		mPosY -= mVelY;
	}
}
int Dot::GetPosX()
{
	return mPosX;
}
int Dot::GetPosY()
{
	return mPosY;
}

Circle& Dot::GetCollider()
{
	return mCollider;
}

void Dot::ShiftColliders()
{
	//Align collider to center of dot
	mCollider.x = mPosX;
	mCollider.y = mPosY;
}

bool Dot::CheckCollision(Circle& a, SDL_Rect& b)
{
	//Closet point
	int cX, cY;
	//find the closet point X
	if (a.x < b.x)
	{
		cX = b.x;
	}
	else if (a.x > b.x + b.w)
	{
		cX = b.x + b.w;
	}
	else
	{
		cX = a.x;
	}

	////find the closet point Y
	if (a.y < b.y)
	{
		cY = b.y;
	}
	else if (a.y > b.y + b.h)
	{
		cY = b.y + b.h;
	}
	else
	{
		cY = a.y;
	}
	//If the closest point is inside the circle
	if (DistanceSquared(a.x, a.y, cX, cY) < a.r * a.r)
	{
		//This box and the circle have collided
		return true;
	}

	//If the shapes have not collided
	return false;
}

bool Dot::CheckCollision(Circle& a, Circle& b)
{
	double totalRadius = a.r + b.r;
	if (DistanceSquared(a.x, a.y, b.x, b.y) < (totalRadius * totalRadius))
	{
		return true;
	}
	return false;
}

double Dot::DistanceSquared(int x1, int y1, int x2, int y2)
{
	double deltaX = x2 - x1;
	double deltaY = y2 - y1;
	return (deltaX * deltaX + deltaY * deltaY);
}

