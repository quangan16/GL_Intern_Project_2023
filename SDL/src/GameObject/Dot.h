#pragma once
#include <SDL.h>
//The Dot that will move around on the screen
struct Circle {
	int x;
	int y;
	int r;
};
class Dot
{
public:
	
	//Dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;
	//Maxium axis velocity of the Dot
	static const int DOT_VEL = 10;
	//Initialize the variable
	Dot(int x, int y);
	~Dot();
	//Taks key presses and adjusts the dot's velocity
	void HandleEvent(SDL_Event& e);
	//Moves the dot
	void Move();
	//Show the Dot on the screen
	
	int GetPosX();
	int GetPosY();
	Circle& GetCollider();
	void ShiftColliders();
	bool CheckCollision(Circle& a, SDL_Rect& b);
	bool CheckCollision(Circle& a, Circle& b);
	double DistanceSquared(int x1, int y1, int x2, int y2);
private:
	//The X and Y offsets of the dot
	int mPosX, mPosY;
	Circle mCollider;

	//The velocity of the dot
	int mVelX, mVelY;
};

