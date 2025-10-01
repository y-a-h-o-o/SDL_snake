#include <SDL3/SDL.h>
#include "graphics_handler.h"

static SDL_FRect player {
	0, 
	(screen_height / 2) - 50, 
	100, 
	100
};

void render_game(SDL_Renderer* renderer) {
	player.x += 5; 
	if(player.x >= screen_width) {
		player.x = -player.w; 
	}
	fill_rect(player, 0, 0, 255, SDL_ALPHA_OPAQUE, renderer);
}

