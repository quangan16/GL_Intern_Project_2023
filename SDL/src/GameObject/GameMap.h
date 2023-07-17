#pragma once


#include "BaseObject.h"
#include "Define.h"
#include "BoxCollider2D.h"
#include <vector>

#define MAX_TILES 20


class GameMap
{
public:
	GameMap();
	~GameMap();
	void LoadMap(const char* name);
	void LoadTiles();
	void DrawMap();
	Map getMap() { return game_map_; }
	std::vector<std::shared_ptr<BoxCollider2D>> tile_map_;

private:
	Map game_map_;
	//std::vector<std::shared_ptr<BoxCollider2D>> tile_map_;
};