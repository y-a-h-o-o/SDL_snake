#ifndef GAME_LOGIC_H

#define GAME_LOGIC_H
#include <SDL3/SDL.h>

enum game_state {
	TITLE, 
	RUNNING, 
	END, 
	CLOSING
}; 

struct Player{
	SDL_FRect box; 
	float vel_x; 
	float vel_y; 
};  

struct Game {
	Player* player; 
};

void update_game_state(const SDL_Event&);

void update_game(); 

const game_state get_game_state(); 

const Game& get_game(); 

#endif
