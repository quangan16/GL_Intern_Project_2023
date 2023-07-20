#pragma once
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

#define TILE_SIZE 128   
#define PLAYER_SPEED 1000.0f
#define JUMP_HEIGHT 200.0f
#define MAX_MAP_X 400
#define MAX_MAP_Y 15

inline bool OnButtonPressed = false;
static bool OnButtonDown = false;
static bool OnButtonUp = false;

typedef struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;
};

static int m_iMapTexture_index = 1;
static int m_iMaptexturesCount = 3;

static int m_iCharacterTexture_index = 1;
static int m_iCharactertexturesCount = 3;