#ifndef GAME_LOGIC_H

#define GAME_LOGIC_H
#include <SDL3/SDL.h>
#include <vector>
#define HEAD 0

constexpr int block_size = 24; 
constexpr int game_width = 24; 
constexpr int game_height = 18;
constexpr int inital_body_size = 4; 
constexpr int start_x = 3; 
constexpr int start_y = 8; 
constexpr int max_apples = 4; 

enum game_state {
	TITLE, 
	RUNNING, 
	END, 
	CLOSING
};

enum player_direction {
	UP, 
	DOWN, 
	LEFT, 
	RIGHT
}; 

struct body_cell {
	int x; 
	int y; 
	player_direction cell_direction; 
}; 

struct Player{
	std::vector<body_cell> body; 
}; 

struct Apple {
	int x; 
	int y; 
}; 

struct Game {
	Player* player; 
	Apple apples[max_apples]; 
};

void update_game_state(const SDL_Event&);

void update_game(); 

const game_state get_game_state(); 

const Game& get_game(); 

#endif
