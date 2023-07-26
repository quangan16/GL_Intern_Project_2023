#include "GameMap.h"

#include <iostream>

#include "GameManager/ResourceManagers.h"
#include "BoxCollider2D.h"
#include "CircleCollider2D.h"


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
			/*if (val > 0)
			{
				if (j > game_map_.max_x_)
				{
					game_map_.max_x_ = j;
				}

				if (i > game_map_.max_y_)
				{
					game_map_.max_y_ = i;
				}
			}*/
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

void GameMap::DrawMap()
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	long long map_x = 0;
	long long map_y = 0;

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
				if (val <= 16)
				{
					auto texture = ResourceManagers::GetInstance()->GetTexture("Ingame_Sprite/Ground_" + std::to_string(val) + ".tga");
					texture->setColor(230, 7, 207);
					texture->SetAlpha(1000);
					auto tile = std::make_shared<BoxCollider2D>(ColliderType::GROUND, Vector2(j, i), true, TILE_SIZE, TILE_SIZE, texture, SDL_FLIP_NONE);
					tile_map_box.push_back(tile);
				}
				if (val >= 17 && val <= 22 )
				{
					auto texture = ResourceManagers::GetInstance()->GetTexture(("Ingame_Sprite/Spike_" + std::to_string(val) + ".tga"));
					auto tile = std::make_shared<BoxCollider2D>(ColliderType::OBSTACLE, Vector2(j ,  i), true, TILE_SIZE , TILE_SIZE, texture, SDL_FLIP_NONE);
					tile->SetColliderPosition(Vector2(j, i + TILE_SIZE/4));
					tile_map_box.push_back(tile);
				}

				if (val == 23)
				{
					auto texture = ResourceManagers::GetInstance()->GetTexture("Ingame_Sprite/Wall_" + std::to_string(val) + ".tga");
					texture->setColor(230, 7, 207);
					texture->SetAlpha(1000);
					auto tile = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE, TILE_SIZE, TILE_SIZE);
					tile->Set2DPosition(j, i);
					noneColliderObjectList.push_back(tile);
				}

				if (val >= 24 && val <= 31 || val == 38)
				{
					auto texture = ResourceManagers::GetInstance()->GetTexture("Ingame_Sprite/Wall_" + std::to_string(val) + ".tga");
					texture->setColor(230, 7, 207);
					texture->SetAlpha(1000);
					auto tile = std::make_shared<BoxCollider2D>(ColliderType::GROUND, Vector2(j, i), true, TILE_SIZE, TILE_SIZE, texture, SDL_FLIP_NONE);
					tile_map_box.push_back(tile);
				}

				if(val == 32)
				{
					auto texture = ResourceManagers::GetInstance()->GetTexture("Ingame_Sprite/Wall_" + std::to_string(val) + ".tga");
					texture->setColor(230, 7, 207);
					texture->SetAlpha(1000);
					auto tile = std::make_shared<BoxCollider2D>(ColliderType::GROUND, Vector2(j, i), true, TILE_SIZE, TILE_SIZE/2, texture, SDL_FLIP_NONE);
					tile_map_box.push_back(tile);
				}

				if (val == 33 || val == 34)
				{
					auto texture = ResourceManagers::GetInstance()->GetTexture("Ingame_Sprite/Portal_" + std::to_string(val) + ".tga");
					auto tile = std::make_shared<BoxCollider2D>(ColliderType::PORTAL_SHIP, Vector2(j, i), true, TILE_SIZE, TILE_SIZE, texture, SDL_FLIP_NONE);
					tile_map_box.push_back(tile);
				}

				if (val == 35)
				{
					auto texture = ResourceManagers::GetInstance()->GetTexture("Ingame_Sprite/Trigger_" + std::to_string(val) + ".tga");
					auto tile = std::make_shared<CircleCollider2D>(ColliderType::JUMP_BOOST_AUTO, Vector2(j, i), true, TILE_SIZE / 6, texture, 1, 19, 1, 0.033f);
					std::cout << "Pos" << tile->GetPosition().y << " " << j << std::endl;
					tile->m_animation->SetPosition(Vector3(j - (TILE_SIZE / 2), i, 0));
					tile->m_animation->SetSize(TILE_SIZE * 2, TILE_SIZE);

					tile_map_circle.push_back(tile);
				}
				
				if (val == 36) {
					auto texture = ResourceManagers::GetInstance()->GetTexture("Ingame_Sprite/Mouse_Trigger_" + std::to_string(val) + ".tga");
					auto tile = std::make_shared<CircleCollider2D>(ColliderType::JUMP_BOOST, Vector2(j,i ), true, TILE_SIZE/2, texture, 1, 30, 1, 0.033f);
					std::cout << "Pos" <<tile->GetPosition().y<<" "<< j << std::endl;
					tile->m_animation->SetSize(TILE_SIZE , TILE_SIZE);
					tile_map_circle.push_back(tile);
				}
				if(val == 39 || val == 41)
				{
					auto texture = ResourceManagers::GetInstance()->GetTexture(("Ingame_Sprite/Spike_" + std::to_string(val) + ".tga"));
					auto tile = std::make_shared<BoxCollider2D>(ColliderType::OBSTACLE, Vector2(j, i), true, TILE_SIZE * 2, TILE_SIZE, texture, SDL_FLIP_NONE);
					tile->SetColliderPosition(Vector2(j, i + TILE_SIZE / 4));
					tile_map_box.push_back(tile);
				}
				if (val == 43)
				{
					auto texture = ResourceManagers::GetInstance()->GetTexture(("Ingame_Sprite/Portal_" + std::to_string(val) + ".tga"));
					auto tile = std::make_shared<BoxCollider2D>(ColliderType::PORTAL_CUBE, Vector2(j, i), true, TILE_SIZE , TILE_SIZE * 4, texture, SDL_FLIP_NONE);
					tile->SetColliderPosition(Vector2(j, i));
					tile_map_box.push_back(tile);
				}
			}
			map_x++;
		}
		map_y++;
	}
}
