#include <SDL3/SDL.h>
#include "game/game_logic.h" 

static game_state current_game_state = TITLE; 

static struct key_state {
	bool up = false; 
	bool down = false; 
	bool left = false; 
	bool right = false; 
} game_key_state; 

static Game game; 

static void init_game() {
	game.player = new Player; 
	game.player->box = new SDL_FRect{0.0f, 0.0f, 50.0f, 50.0f};
	game.player->vel_x = 5.0; 
	game.player->vel_y = 5.0; 
} 

static void close_game() {
	delete game.player->box; 
	game.player->box = nullptr; 
	delete game.player; 
	game.player = nullptr; 
	SDL_Log("Player Deleted ...");
}

void update_game_state(const SDL_Event& e) {
	if(e.type == SDL_EVENT_QUIT) {
		SDL_Log("Shutting Down ...");
		current_game_state = CLOSING; 	
	} else if(e.type == SDL_EVENT_KEY_DOWN) {
		switch(e.key.scancode) {
			case SDL_SCANCODE_UP: game_key_state.up = true; break; 
			case SDL_SCANCODE_DOWN: game_key_state.down = true; break; 
			case SDL_SCANCODE_LEFT: game_key_state.left = true; break;
			case SDL_SCANCODE_RIGHT: game_key_state.right = true; break;
		}
	} else if(e.type == SDL_EVENT_KEY_UP) {
		switch(e.key.scancode) {
			case SDL_SCANCODE_UP: game_key_state.up = false; break; 
			case SDL_SCANCODE_DOWN: game_key_state.down = false; break; 
			case SDL_SCANCODE_LEFT: game_key_state.left = false; break;
			case SDL_SCANCODE_RIGHT: game_key_state.right = false; break;
		}	
	}
}

void update_game() {
	switch (current_game_state) {
		// TODO: Title and End states have nothing right now. 
		case TITLE: current_game_state = RUNNING; init_game(); break;
		case RUNNING: 
		{
			if(game_key_state.right) {
				game.player->box->x += 5.0f; 
			} 
			if(game_key_state.left) {
				game.player->box->x -= 5.0f; 
			} 
			if(game_key_state.up) {
				game.player->box->y -= 5.0f; 	
			} 
			if(game_key_state.down) {
				game.player->box->y += 5.0f; 
			}
		} break; 	
		case END: break;
		case CLOSING: close_game(); break; 
	}		
}

const game_state get_game_state() {
	return current_game_state; 	
}

const Game& get_game() {
	return game; 
}
