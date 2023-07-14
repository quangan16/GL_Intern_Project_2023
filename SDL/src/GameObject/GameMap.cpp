#include "GameMap.h"
#include "GameManager/ResourceManagers.h"
#include "BoxCollider2D.h"


GameMap::GameMap()
{
}

GameMap::~GameMap()
{
}

void GameMap::LoadMap(const char* name)
{
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL)
	{
		printf("Can't open file");
		return;
	}

	game_map_.max_x_ = 0;
	game_map_.max_y_ = 0;
	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			fscanf_s(fp, "%d", &game_map_.tile[i][j]);
			int val = game_map_.tile[i][j];
			if (val > 0)
			{
				if (j > game_map_.max_x_)
				{
					game_map_.max_x_ = j;
				}

				if (i > game_map_.max_y_)
				{
					game_map_.max_y_ = i;
				}
			}
		}
		printf("\n");
	}

	game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;
	game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;

	game_map_.start_x_ = 0;
	game_map_.start_y_ = 0;

	game_map_.file_name_ = (char*)name;
	fclose(fp);
}

void GameMap::LoadTiles()
{
	/*char file_img[30];
	FILE * fp = NULL;

	for (int i = 0; i < MAX_TILES; i++)
	{
		sprintf_s(file_img, "map/%d.png", i);
		fopen_s(&fp, file_img, "rb");
		if (fp == NULL)
		{
			continue;
		}
		fclose(fp);

		tile_map_[i].SetTexture(ResourceManagers::GetInstance()->GetTexture(file_img));
	}*/
}

void GameMap::DrawMap(SDL_Renderer* renderer)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;

	map_x = game_map_.start_x_ / TILE_SIZE;
	//x1 = (game_map_.start_x_ % TILE_SIZE) * -1;
	x2 = MAX_MAP_X * TILE_SIZE;

	map_y = game_map_.start_y_ / TILE_SIZE;
	//y1 = (game_map_.start_y_ % TILE_SIZE) * -1;
	y2 = MAX_MAP_Y * TILE_SIZE;


	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		map_x = game_map_.start_x_ / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int val = game_map_.tile[map_y][map_x];
			if (val > 0)
			{
				auto texture = ResourceManagers::GetInstance()->GetTexture(std::to_string(val) + ".tga");
				auto tile = std::make_shared<BoxCollider2D>(ColliderType::GROUND, Vector2(j,i), true, TILE_SIZE, TILE_SIZE, texture, SDL_FLIP_NONE);
				tile->Draw(renderer);
			}
			map_x++;
		}
		map_y++;
	}
}
