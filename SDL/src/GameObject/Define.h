#pragma once
#include<memory>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

#define TILE_SIZE 80   
#define PLAYER_SPEED 1000.0f
#define JUMP_HEIGHT 200.0f
#define MAX_MAP_X 400
#define MAX_MAP_Y 15
#define SAVE_PATH = "Data/save_data.txt"

class GameStateBase;
const float tile_offset = 128.0f * 4;
inline bool OnButtonPressed = false;
inline bool OnButtonDown = false;
inline bool OnButtonUp = false;


inline std::shared_ptr<GameStateBase> g_stateControllerPtr;

typedef struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;
};

inline int m_iMapTexture_index = 1;
inline int m_iMaptexturesCount = 3;

inline int m_iCharacterTexture_index = 1;
inline int m_iCharactertextures_count = 3;

inline int m_iShipTexture_index = 1;
inline int m_iShipTexture_count = 3;

inline int m_iWaveTexture_index = 1;
inline int m_iWaveTexture_count = 3;

inline int m_iHighest_process_level_1 = 0;
inline int m_iHighest_process_level_2 = 0;
inline int m_iHighest_process_level_3 = 0;

inline int r = 2, g = 2, b = 2, a = 256, index = 0;
inline int interval = 1;