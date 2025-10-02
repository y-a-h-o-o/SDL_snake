#include <SDL3/SDL.h>
#include "game/game_graphics.h"
#include "game/game_logic.h"
#include "graphics_handler.h"

void render_game(SDL_Renderer* renderer) {
	const game_state state = get_game_state();
	if(state == CLOSING) {
		return; 
	}
	const Game& game = get_game(); 
	fill_rect(game.player->box, 0, 0, 255, SDL_ALPHA_OPAQUE, renderer);
}
