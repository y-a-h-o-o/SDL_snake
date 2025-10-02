#include <SDL3/SDL.h>
#include <string>
#include "game/game_graphics.h"
#include "game/game_logic.h"
#include "graphics_handler.h"

void render_game(SDL_Renderer* renderer) {
	const game_state state = get_game_state();
	switch(state) {
		case TITLE: {
			const char *title = "SDL Snake!"; 
			const char *play_message = "<Press Enter to play>";
			const char *quit_message = "<Or Press ESC to quit>";
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); 
			SDL_SetRenderScale(renderer, 4.0f, 4.0f);
			SDL_RenderDebugText(renderer, 33, 30, title); 
			SDL_SetRenderScale(renderer, 1.0f, 1.0f); 
			SDL_RenderDebugText(renderer, 200, 200, play_message);
			SDL_SetRenderScale(renderer, 1.0f, 1.0f); 
			SDL_RenderDebugText(renderer, 197, 250, quit_message);
		} break; 
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
		case END: {
			const char *title = "Oops you died!"; 		
			const char *play_message = "<Press Enter to play again>";
			const char *quit_message = "<Or Press ESC to quit>";
			std::string high_score = "Your high score so far is: " + std::to_string(get_score()) + "!"; 
			const char *score_message = high_score.c_str(); 
			
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); 
			SDL_SetRenderScale(renderer, 4.0f, 4.0f);
			SDL_RenderDebugText(renderer, 17, 30, title); 
			SDL_SetRenderScale(renderer, 1.0f, 1.0f); 
			SDL_RenderDebugText(renderer, 180, 250, play_message);
			SDL_SetRenderScale(renderer, 1.0f, 1.0f); 
			SDL_RenderDebugText(renderer, 200, 350, quit_message);
			SDL_SetRenderScale(renderer, 1.0f, 1.0f); 
			SDL_RenderDebugText(renderer, 175, 200, score_message);
		} break; 
	}
}
