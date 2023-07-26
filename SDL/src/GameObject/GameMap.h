#pragma once


#include "BaseObject.h"
#include "Define.h"
#include "BoxCollider2D.h"
#include "CircleCollider2D.h"
#include <vector>

#define MAX_TILES 20


class GameMap
{
public:
	GameMap();
	~GameMap();
	void LoadMap(std::string name);
	void LoadTiles();
	void DrawMap();
	Map getMap() { return game_map_; }
	std::vector<std::shared_ptr<Sprite2D>> noneColliderObjectList;
	std::vector<std::shared_ptr<BoxCollider2D>> tile_map_box;
	std::vector<std::shared_ptr<CircleCollider2D>> tile_map_circle;
private:
	Map game_map_;
	//std::vector<std::shared_ptr<BoxCollider2D>> tile_map_;
};