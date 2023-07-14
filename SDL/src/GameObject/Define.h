#pragma once
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define TILE_SIZE 128
#define PLAYER_SPEED 1000.0f
#define MAX_MAP_X 400
#define MAX_MAP_Y 20

typedef struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;
};