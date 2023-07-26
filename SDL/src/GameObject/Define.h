#pragma once
#include<memory>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define TILE_SIZE 100   
#define PLAYER_SPEED 900.0f
#define JUMP_HEIGHT 200.0f
#define MAX_MAP_X 960
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
inline bool g_trigger = false;

inline std::shared_ptr<Sound> m_Sound;
inline GameStateBase* g_stateControllerPtr;

typedef struct Map
{
	int start_x_;
	int start_y_;

	long long max_x_;
	long long max_y_;

	long long tile[MAX_MAP_Y][MAX_MAP_X];
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
inline int m_Highscore[3];

inline bool isMuted = false;

inline int r = 2, g = 2, b = 2, a = 256, index = 0;
inline int interval = 1;

//https://www.all8.com/tools/bpm/