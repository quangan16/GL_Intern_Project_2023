#pragma once


#include "BaseObject.h"
#include "Define.h"

#define MAX_TILES 20


class GameMap
{
public:
	GameMap();
	~GameMap();
	void LoadMap(const char* name);
	void LoadTiles();
	void DrawMap(SDL_Renderer* renderer);

private:
	Map game_map_;
};