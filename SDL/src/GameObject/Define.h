#pragma once
#include<memory>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define TILE_SIZE 100   
#define PLAYER_SPEED 900.0f
#define JUMP_HEIGHT 200.0f
#define MAX_MAP_X 1000
#define MAX_MAP_Y 24

class GameStateBase;
class Sound;
const float tile_offset = 100.0f * 4;
inline bool OnButtonPressed = false;
inline bool OnButtonDown = false;
inline bool OnButtonUp = false;
inline bool canDrawEvent;
inline float timer = 0.0f;

inline bool m_savePointMode;
inline bool m_immortalMode;
inline bool g_trigger = false;

inline std::shared_ptr<Sound> m_Sound;
inline std::shared_ptr<GameStateBase> g_stateControllerPtr;

typedef struct Map
{
	int start_x_;
	int start_y_;

	long long max_x_;
	long long max_y_;

	long long tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;
};

typedef struct Map_Color
{
	int r;
	int g;
	int b;
	int a;
};

inline int m_iMapTexture_index = 1;
inline int m_iMaptexturesCount = 3;

inline int m_iCharacterTexture_index = 1;
inline int m_iCharactertextures_count = 3;

inline int m_iShipTexture_index = 1;
inline int m_iShipTexture_count = 3;

inline int m_iWaveTexture_index = 1;
inline int m_iWaveTexture_count = 3;

inline int m_iBallTexture_index = 1;
inline int m_iBallTexture_count = 3;

inline int m_iHighest_process_level_1 = 0;
inline int m_iHighest_process_level_2 = 0;
inline int m_iHighest_process_level_3 = 0;
inline int m_Highscore[3];

inline bool isMuted = false;

inline int r = 2, g = 2, b = 2, a = 256, index = 0;
inline int interval = 1;
inline int index_color = 0;

inline Map_Color map_color[3][3] =
{
	{
		{52, 161, 245}, {28, 217, 75}, {166 , 217, 65}
	},
	{
		{210, 28, 217}, {217, 28, 100}, {217, 97, 28}
	},
	{
		{217, 116, 28}, {28, 217, 167}, {217, 28, 28}
	}
};



//https://www.all8.com/tools/bpm/