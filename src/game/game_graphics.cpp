#include <SDL3/SDL.h>
#include "game/game_graphics.h"
#include "game/game_logic.h"
#include "graphics_handler.h"

void render_game(SDL_Renderer* renderer) {
	const game_state state = get_game_state();
	switch(state) {
		case TITLE: break; 
		case END : 
		case RUNNING: {
			const Game& game = get_game(); 
			Player* p = game.player;
			for(int i = 0; i < (p->body).size(); i++) {
				SDL_FRect temp = {
					(block_size * p->body[i].x), 
					(block_size * p->body[i].y), 
					block_size, 
					block_size
				}; 

				if(i == HEAD) {
					fill_rect(temp, 255, 255, 0, SDL_ALPHA_OPAQUE, renderer); 	
				} else {
					fill_rect(temp, 0, 128, 0, SDL_ALPHA_OPAQUE, renderer);
				}
			}

			for(int i = 0; i < max_apples; i++) {
				SDL_FRect temp = {
					(block_size * game.apples[i].x), 
					(block_size * game.apples[i].y), 
					block_size,
					block_size
				};
				fill_rect(temp, 0, 0, 255, SDL_ALPHA_OPAQUE, renderer); 
			}
		} break; 
		case CLOSING: return;  
	}
}
